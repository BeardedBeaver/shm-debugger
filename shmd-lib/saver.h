#pragma once

#include <ostream>
#include <vector>

class Saver {
public:
    explicit Saver(std::ostream& stream, int32_t fps);

    void save(const std::vector<char>& bytes);

private:
    std::ostream& m_stream;
};
