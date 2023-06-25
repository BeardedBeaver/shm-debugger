#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>

#include "loader.h"
#include "saver.h"

namespace fs = std::filesystem;

class TemporaryFile {
public:
    TemporaryFile() {
        m_tempDir = fs::temp_directory_path();
        m_tempPath = m_tempDir / "dump.dat";
    }

    ~TemporaryFile() {
        if (fs::exists(m_tempPath)) {
            fs::remove(m_tempPath);
            std::cout << "Temporary file deleted: " << m_tempPath << std::endl;
        }
    }

    const fs::path& getPath() const {
        return m_tempPath;
    }

private:
    fs::path m_tempDir;
    fs::path m_tempPath;
};

TEST(LoaderSaverTest, Breathing) {
    std::string s1 = "The quick brown fox jumps over the lazy dog";
    std::string s2 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec vel dolor vel tortor posuere finibus non id orci. Sed porta maximus vulputate";
    std::string s3 = "REC is seriously awesome!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";

    int length = 100000;
    std::string s4;
    s4.reserve(length);
    for (int i = 0; i < length; ++i) {
        char c = 'A' + (i % 26);
        s4.push_back(c);
    }

    auto v1 = std::vector<char>(s1.begin(), s1.end());
    auto v2 = std::vector<char>(s2.begin(), s2.end());
    auto v3 = std::vector<char>(s3.begin(), s3.end());
    auto v4 = std::vector<char>(s4.begin(), s4.end());

    TemporaryFile file;

    {
        std::ofstream out(file.getPath(), std::ios::binary);

        ASSERT_TRUE(out);
        ASSERT_TRUE(out.is_open());

        Saver saver(out, 42);

        saver.save(v1);
        saver.save(v2);
        saver.save(v3);
        saver.save(v4);
    }

    {
        std::ifstream in(file.getPath(), std::ios::binary);

        ASSERT_TRUE(in);
        ASSERT_TRUE(in.is_open());

        Loader loader(in);
        ASSERT_EQ(loader.getFps(), 42);

        auto d1 = loader.load();
        auto d2 = loader.load();
        auto d3 = loader.load();
        auto d4 = loader.load();

        ASSERT_EQ(v1, d1);
        ASSERT_EQ(v2, d2);
        ASSERT_EQ(v3, d3);
        ASSERT_EQ(v4, d4);
    }
}
