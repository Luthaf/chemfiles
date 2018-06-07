// Chemfiles, a modern library for chemistry file reading and writing
// Copyright (C) Guillaume Fraux and contributors -- BSD license

#ifndef CHEMFILES_GZ_FILES_HPP
#define CHEMFILES_GZ_FILES_HPP

#include <streambuf>
#include <vector>

#include <zlib.h>

#include "chemfiles/File.hpp"

namespace chemfiles {

class gzstreambuf: public std::streambuf {
public:
    gzstreambuf(size_t buffer_size = 512);
    ~gzstreambuf() override;

    void open(const std::string& filename, const std::string& openmode);

    int_type underflow() override;
    int_type overflow(int_type ch) override;

    int sync() override;
    bool is_open() const;

    std::streampos seekpos(std::streampos offset, std::ios_base::openmode which) override {
        return pubseekoff(offset, std::ios_base::beg, which);
    }

    std::streampos seekoff(std::streamoff offset, std::ios_base::seekdir way, std::ios_base::openmode which) override;

private:
    std::vector<char> buffer_;
    gzFile file_;
};


/// A gziped text file
class GzFile final: public TextFile {
public:
    /// Open the file with the given `filename` using the specified `mode`
    GzFile(const std::string& filename, File::Mode mode);

private:
    gzstreambuf buffer_;
};

} // namespace chemfiles

#endif
