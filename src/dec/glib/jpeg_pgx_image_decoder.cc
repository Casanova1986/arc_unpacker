#include "dec/glib/jpeg_pgx_image_decoder.h"
#include "algo/format.h"
#include "algo/range.h"
#include "dec/glib/custom_lzss.h"
#include "io/memory_stream.h"

// This is a bit different from plain PGX - namely, it involves two LZSS passes.

using namespace au;
using namespace au::dec::glib;

static const bstr magic = "PGX\x00"_b;

static bstr extract_pgx_stream(const bstr &jpeg_data)
{
    bstr output;
    output.reserve(jpeg_data.size());
    io::MemoryStream jpeg_stream(jpeg_data);
    jpeg_stream.skip(2); // soi
    jpeg_stream.skip(2); // header chunk
    jpeg_stream.skip(jpeg_stream.read_u16_be() - 2);
    while (jpeg_stream.read_u16_be() == 0xFFE3)
        output += jpeg_stream.read(jpeg_stream.read_u16_be() - 2);
    return output;
}

bool JpegPgxImageDecoder::is_recognized_impl(io::File &input_file) const
{
    u16 marker = input_file.stream.read_u16_be();
    // soi
    if (marker != 0xFFD8)
        return false;
    marker = input_file.stream.read_u16_be();
    // header chunk
    if (marker != 0xFFE0)
        return false;
    input_file.stream.skip(input_file.stream.read_u16_be() - 2);
    // PGX start
    marker = input_file.stream.read_u16_be();
    if (marker != 0xFFE3)
        return false;
    if (input_file.stream.read_u16_be() < magic.size())
        return false;
    return input_file.stream.read(magic.size()) == magic;
}

res::Image JpegPgxImageDecoder::decode_impl(
    const Logger &logger, io::File &input_file) const
{
    const auto pgx_data = extract_pgx_stream(input_file.stream.read_to_eof());
    io::MemoryStream pgx_stream(pgx_data);

    pgx_stream.skip(magic.size());
    pgx_stream.skip(4);
    const auto width = pgx_stream.read_u32_le();
    const auto height = pgx_stream.read_u32_le();
    const auto transparent = pgx_stream.read_u16_le() != 0;
    pgx_stream.skip(2);
    const auto source_size = pgx_stream.read_u32_le();
    const auto target_size = width * height * 4;
    pgx_stream.skip(8);

    if (!transparent)
    {
        pgx_stream.skip(8);
        const auto tmp1 = pgx_stream.read_u32_le();
        const auto tmp2 = pgx_stream.read_u32_le();
        const auto extra_size = (tmp2 & 0x00FF00FF) | (tmp1 & 0xFF00FF00);
        // why?
        custom_lzss_decompress(pgx_stream, extra_size);
    }

    const auto target = custom_lzss_decompress(
        pgx_stream.read_to_eof(), target_size);

    res::Image image(width, height, target, res::PixelFormat::BGRA8888);
    if (!transparent)
        for (auto &c : image)
            c.a = 0xFF;
    return image;
}

static auto _ = dec::register_decoder<JpegPgxImageDecoder>("glib/jpeg-pgx");