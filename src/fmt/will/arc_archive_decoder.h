#pragma once

#include "fmt/archive_decoder.h"

namespace au {
namespace fmt {
namespace will {

    class ArcArchiveDecoder final : public ArchiveDecoder
    {
    public:
        ArcArchiveDecoder();
        ~ArcArchiveDecoder();
    protected:
        bool is_recognized_impl(File &) const override;
        std::unique_ptr<ArchiveMeta> read_meta_impl(File &) const override;
        std::unique_ptr<File> read_file_impl(
            File &, const ArchiveMeta &, const ArchiveEntry &) const override;
        void preprocess(
            File &, ArchiveMeta &, const FileSaver &) const override;
    private:
        struct Priv;
        std::unique_ptr<Priv> p;
    };

} } }
