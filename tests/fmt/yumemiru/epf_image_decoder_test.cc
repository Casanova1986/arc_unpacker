#include "fmt/yumemiru/epf_image_decoder.h"
#include "test_support/catch.hh"
#include "test_support/decoder_support.h"
#include "test_support/file_support.h"
#include "test_support/image_support.h"

using namespace au;
using namespace au::fmt::yumemiru;

static const std::string dir = "tests/fmt/yumemiru/files/epf/";

static void do_test(
    const std::string &input_path, const std::string &expected_path)
{
    const EpfImageDecoder decoder;
    const auto input_file = tests::file_from_path(dir + input_path);
    const auto expected_file = tests::image_from_path(dir + expected_path);
    const auto actual_file = tests::decode(decoder, *input_file);
    tests::compare_images(*expected_file, actual_file);
}

TEST_CASE("Yumemiru EPF images", "[fmt]")
{
    do_test("IF_cg_bg_minyusyu_c.epf", "IF_cg_bg_minyusyu_c-out.png");
}