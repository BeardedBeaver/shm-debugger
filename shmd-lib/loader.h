#pragma once

#include <array>
#include <istream>
#include <vector>

class Loader {
public:
    explicit Loader(std::istream& stream);

    std::vector<char> load();
    [[nodiscard]] int32_t getFps() const;
    [[nodiscard]] std::array<char, 4> getId() const;

private:
    std::istream& m_stream;
    int32_t m_fps;
    std::array<char, 4> m_id;
};
