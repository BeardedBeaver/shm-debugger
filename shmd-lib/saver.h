#pragma once

#include <array>
#include <ostream>
#include <vector>

class Saver {
public:
    explicit Saver(std::ostream& stream, int32_t fps, std::array<char, 4> id);

    void save(const std::vector<char>& bytes);

private:
    std::ostream& m_stream;
};
