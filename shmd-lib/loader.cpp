#include "loader.h"

#include <cassert>
#include <iostream>

#include <zlib.h>

Loader::Loader(std::istream& stream)
    : m_stream(stream),
      m_fps{} {
    assert(m_stream);
    std::string header(8, '\0');
    m_stream.read(&header[0], 8);

    if (header != "RECROCKS") {
        throw std::invalid_argument("Invalid file format.");
    }

    m_stream.read(reinterpret_cast<char*>(&m_fps), sizeof(m_fps));
    m_stream.read(m_id.data(), m_id.size());

    // Skip padding data
    [[maybe_unused]] int32_t paddingValue = 0;
    m_stream.ignore(14 * sizeof(paddingValue));
}

std::vector<char> Loader::load() {
    uint32_t compressedDataLength;
    m_stream.read(reinterpret_cast<char*>(&compressedDataLength), sizeof(compressedDataLength));

    uint32_t rawDataLength;
    m_stream.read(reinterpret_cast<char*>(&rawDataLength), sizeof(rawDataLength));

    if (m_stream.eof()) {
        return {};
    }

    std::unique_ptr<char[]> compressedData(new char[compressedDataLength]);
    m_stream.read(compressedData.get(), compressedDataLength);

    uLongf uncompressedSize = rawDataLength;
    std::vector<char> uncompressedData(uncompressedSize);

    int result = uncompress(reinterpret_cast<Bytef*>(&uncompressedData[0]), &uncompressedSize,
                            reinterpret_cast<const Bytef*>(compressedData.get()), compressedDataLength);

    if (result != Z_OK) {
        throw std::invalid_argument("Failed to decompress data. File is corrupted?");
    }

    return uncompressedData;
}

int Loader::getFps() const {
    return m_fps;
}

std::array<char, 4> Loader::getId() const {
    return m_id;
}
