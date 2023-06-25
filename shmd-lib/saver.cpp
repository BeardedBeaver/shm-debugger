#include "saver.h"

#include <cassert>

#include <zlib.h>

Saver::Saver(std::ostream& stream, int32_t fps, std::array<char, 4> id)
    : m_stream(stream) {
    assert(m_stream);
    std::string header = "RECROCKS";
    m_stream.write(header.c_str(), header.length());
    m_stream.write(reinterpret_cast<const char*>(&fps), sizeof(fps));

    m_stream.write(id.data(), id.size());

    int32_t paddingValue = 0;
    int paddingLength = 14;
    for (int i = 0; i < paddingLength; ++i) {
        m_stream.write(reinterpret_cast<const char*>(&paddingValue), sizeof(paddingValue));
    }
}

void Saver::save(const std::vector<char>& bytes) {
    uLongf compressedSize = compressBound(static_cast<uLongf>(bytes.size()));
    std::unique_ptr<char[]> compressedData(new char[compressedSize]);

    compress2(reinterpret_cast<Bytef*>(compressedData.get()), &compressedSize,
              reinterpret_cast<const Bytef*>(bytes.data()), static_cast<uLong>(bytes.size()),
              Z_DEFAULT_COMPRESSION);

    uint32_t compressedDataLength = compressedSize;
    m_stream.write(reinterpret_cast<const char*>(&compressedDataLength), sizeof(compressedDataLength));
    uint32_t rawDataLength = bytes.size();
    m_stream.write(reinterpret_cast<const char*>(&rawDataLength), sizeof(rawDataLength));
    m_stream.write(compressedData.get(), static_cast<std::streamsize>(compressedSize));
}
