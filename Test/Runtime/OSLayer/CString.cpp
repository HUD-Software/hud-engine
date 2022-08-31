#include <OSLayer/CString.h>


HUD_TEST_NAMESPACE
{
    template<typename TCharType>
    i32 call_format_vargs(TCharType* buffer, u32 buffer_size, const TCharType* format, ...) {
        va_list args;
        va_start(args, format);
        i32 count = CString::format_vargs(buffer, buffer_size, format, args);
        va_end(args);
        return count;
    }
} // HUD_TEST_NAMESPACE

TEST(CString, is_pure_ansi) {
    for (ansichar cur = 0; cur < hud::ansichar_max; cur++) {
        ansichar text[2] = { cur,'\0' };
        ASSERT_TRUE(hud::CString::is_pure_ansi(text));
    }
    for (wchar cur = 0; cur < hud::wchar_max; cur++) {
        wchar text[2] = { cur, L'\0' };
        if (hud::Char::is_pure_ansi(cur)) {
            ASSERT_TRUE(hud::CString::is_pure_ansi(text));
        }
        else {
            ASSERT_FALSE(hud::CString::is_pure_ansi(text));
        }
    }
}

TEST(CString, is_pure_ansi_safe) {
    using namespace hud;

    for (ansichar cur = 0; cur < ansichar_max; cur++) {
        const ansichar text[2] = { cur,'\0' };
        ASSERT_TRUE(CString::is_pure_ansi_safe(text, 1));
    }
    for (wchar cur = 0; cur < wchar_max; cur++) {
        const wchar text[2] = { cur, L'\0' };
        if (Char::is_pure_ansi(cur)) {
            ASSERT_TRUE(CString::is_pure_ansi_safe(text, 1));
        }
        else {
            ASSERT_FALSE(CString::is_pure_ansi_safe(text, 1));
        }
    }
}

TEST(CString, is_null_or_empty) {
    using namespace hud;

    static constexpr const ansichar* const no_null_empty = "abc";
    static constexpr const ansichar* const empty = "";
    static constexpr const ansichar* const null = nullptr;

    ASSERT_FALSE(CString::is_null_or_empty(no_null_empty));
    ASSERT_TRUE(CString::is_null_or_empty(empty));
    ASSERT_TRUE(CString::is_null_or_empty(null));

    static constexpr const ansichar* const wide_no_null_empty = "abc";
    static constexpr const ansichar* const wide_empty = "";
    static constexpr const ansichar* const wide_null = nullptr;

    ASSERT_FALSE(CString::is_null_or_empty(wide_no_null_empty));
    ASSERT_TRUE(CString::is_null_or_empty(wide_empty));
    ASSERT_TRUE(CString::is_null_or_empty(wide_null));

}

TEST(CString, copy) {
    using namespace hud;

    static constexpr const ansichar* const src = "abc";
    ansichar dest[4];

    ASSERT_TRUE(CString::copy(dest, src) == dest);
    ASSERT_TRUE(dest[0] == 'a' && dest[1] == 'b' && dest[2] == 'c' && dest[3] == '\0');

    static constexpr const wchar* const wide_src = L"abc";
    wchar wide_dest[4];
    ASSERT_TRUE(CString::copy(wide_dest, wide_src) == wide_dest);
    ASSERT_TRUE(wide_dest[0] == L'a' && wide_dest[1] == L'b' && wide_dest[2] == L'c' && wide_dest[3] == L'\0');

    // Thoses crash
    //ASSERT_TRUE(CString::copy((ansichar*)nullptr, nullptr) == nullptr);
    //ASSERT_TRUE(CString::copy((wchar*)nullptr, nullptr) == nullptr);
}

TEST(CString, copy_safe) {
    using namespace hud;

    static constexpr const ansichar* const src = "abc";
    ansichar dest[4];

    ASSERT_TRUE(CString::copy_safe(dest, 4, src));
    ASSERT_TRUE(CString::copy_safe(dest, 4, src));
    ASSERT_EQ(dest[0], 'a');
    ASSERT_EQ(dest[1], 'b');
    ASSERT_EQ(dest[2], 'c');
    ASSERT_EQ(dest[3], '\0');

    static constexpr const wchar* const wide_src = L"abc";
    wchar wide_dest[4];

    ASSERT_TRUE(CString::copy_safe(wide_dest, 4, wide_src));

    ASSERT_TRUE(CString::copy_safe(wide_dest, 4, wide_src));
    ASSERT_EQ(wide_dest[0], L'a');
    ASSERT_EQ(wide_dest[1], L'b');
    ASSERT_EQ(wide_dest[2], L'c');
    ASSERT_EQ(wide_dest[3], L'\0');

    

    // Thoses crash
    // ASSERT_FALSE(CString::copy_safe(nullptr, 0, src));
    // ASSERT_FALSE(CString::copy_safe(dest, 4, nullptr));
    // ASSERT_FALSE(CString::copy_safe(dest, 0, src));
    // ASSERT_FALSE(CString::copy_safe(nullptr, 0, wide_src));
    // ASSERT_FALSE(CString::copy_safe(wide_dest, 4, nullptr));
    // ASSERT_FALSE(CString::copy_safe(wide_dest, 0, wide_src));
    // ASSERT_FALSE(CString::copy_safe((ansichar*)nullptr, 4, nullptr));
    // ASSERT_FALSE(CString::copy_safe((wchar*)nullptr, 4, nullptr));
    //ASSERT_FALSE(CString::copy_safe(wide_dest, 3, wide_src)); // No place for null-terminator character
}

TEST(CString, copy_partial) {
    using namespace hud;

    static constexpr const ansichar* const src = "abc";
    ansichar dest[4];

    ASSERT_TRUE(CString::copy_partial(dest, src, 2) == dest);
    ASSERT_TRUE(dest[0] == 'a' && dest[1] == 'b');

    ASSERT_TRUE(CString::copy_partial(dest, src, 0) == dest);
    ASSERT_TRUE(dest[0] == 'a' && dest[1] == 'b');

    ASSERT_TRUE(CString::copy_partial(dest, src, 2) == dest);
    ASSERT_TRUE(dest[0] == 'a' && dest[1] == 'b');


    static constexpr const wchar* const wide_src = L"abc";
    wchar wide_dest[4];

    ASSERT_TRUE(CString::copy_partial(wide_dest, wide_src, 2) == wide_dest);
    ASSERT_TRUE(wide_dest[0] == L'a' && wide_dest[1] == L'b');

    ASSERT_TRUE(CString::copy_partial(wide_dest, wide_src, 0) == wide_dest);
    ASSERT_TRUE(wide_dest[0] == L'a' && wide_dest[1] == L'b');

    ASSERT_TRUE(CString::copy_partial(wide_dest, wide_src, 2) == wide_dest);
    ASSERT_TRUE(wide_dest[0] == L'a' && wide_dest[1] == L'b');

    // Thoses crash
    //ASSERT_FALSE(CString::copy_partial(nullptr, src, 2) == nullptr);
    //ASSERT_FALSE(CString::copy_partial(dest, nullptr, 2) == nullptr);
    //ASSERT_FALSE(CString::copy_partial(nullptr, wide_src, 2) == nullptr);
    //ASSERT_FALSE(CString::copy_partial(wide_dest, nullptr, 2) == nullptr);
    //ASSERT_FALSE(CString::copy_partial((ansichar*)nullptr, nullptr, 2) == nullptr);
    //ASSERT_FALSE(CString::copy_partial((wchar*)nullptr, nullptr, 2) == nullptr);
}

TEST(CString, copy_partial_safe) {
    using namespace hud;

    static constexpr const ansichar* const src = "abc";
    ansichar dest[4];

    ASSERT_TRUE(CString::copy_partial_safe(dest, 4, src, 2));
    ASSERT_TRUE(dest[0] == 'a' && dest[1] == 'b' && dest[2] == '\0');

    ASSERT_TRUE(CString::copy_partial_safe(dest, 4, src, 0));
    ASSERT_TRUE(dest[0] == '\0');

    static constexpr const wchar* const wide_src = L"abc";
    wchar wide_dest[4];

    ASSERT_TRUE(CString::copy_partial_safe(wide_dest, 4, wide_src, 2));
    ASSERT_TRUE(wide_dest[0] == L'a' && wide_dest[1] == L'b' && wide_dest[2] == L'\0');

    ASSERT_TRUE(CString::copy_partial_safe(wide_dest, 4, wide_src, 0));
    ASSERT_TRUE(dest[0] == L'\0');

    // Thoses crash
    //ASSERT_FALSE(CString::copy_partial_safe(dest, 2, src, 2)); // Not enough place for null-terminator character
    //ASSERT_FALSE(CString::copy_partial_safe(dest, 0, src, 2)); // destination is too small
    //ASSERT_FALSE(CString::copy_partial_safe(wide_dest, 2, wide_src, 2)); // Not enough place for null-terminator character
    //ASSERT_FALSE(CString::copy_partial_safe(wide_dest, 0, wide_src, 2)); // destination is too small
    //ASSERT_FALSE(CString::copy_partial_safe(nullptr, 4, src, 2)); // destination is nullptr
    //ASSERT_FALSE(CString::copy_partial_safe(dest, 4, nullptr, 2)); // source is nullptr
    //ASSERT_FALSE(CString::copy_partial_safe(nullptr, 4, wide_src, 2)); // destination is nullptr
    //ASSERT_FALSE(CString::copy_partial_safe(wide_dest, 4, nullptr, 2)); // source is nullptr
    //ASSERT_FALSE(CString::copy_partial_safe((ansichar*)nullptr, 4, nullptr, 2)); // destination and source are nullptr
    //ASSERT_FALSE(CString::copy_partial_safe((wchar*)nullptr, 4, nullptr, 2)); // destination and source are nullptr
}

TEST(CString, append) {
    using namespace hud;

    static constexpr const ansichar* const src = "de";
    ansichar dest[6] = { 'a', 'b', 'c', '\0' };
    ASSERT_TRUE(CString::append(dest, src) == dest);
    ASSERT_TRUE(dest[0] == 'a' && dest[1] == 'b' && dest[2] == 'c' && dest[3] == 'd' && dest[4] == 'e' && dest[5] == '\0');

    static constexpr const wchar* const wide_src = L"de";
    wchar wide_dest[6] = { L'a', L'b', L'c', L'\0' };
    ASSERT_TRUE(CString::append(wide_dest, wide_src) == wide_dest);
    ASSERT_TRUE(wide_dest[0] == L'a' && wide_dest[1] == L'b' && wide_dest[2] == L'c' && wide_dest[3] == L'd' && wide_dest[4] == L'e' && wide_dest[5] == L'\0');

    // Thoses crash
    //ASSERT_FALSE(CString::append(nullptr, src));
    //ASSERT_FALSE(CString::append(dest, nullptr));
    //ASSERT_FALSE(CString::append(nullptr, wide_src));
    //ASSERT_FALSE(CString::append(wide_dest, nullptr));
    //ASSERT_FALSE(CString::append((ansichar*)nullptr, nullptr));
    //ASSERT_FALSE(CString::append((wchar*)nullptr, nullptr));
}

TEST(CString, append_safe) {
    using namespace hud;

    static constexpr const ansichar* const src = "de";
    ansichar dest[6] = { 'a', 'b', 'c', '\0' };
    ASSERT_TRUE(CString::append_safe(dest, 6, src));
    ASSERT_TRUE(dest[0] == 'a' && dest[1] == 'b' && dest[2] == 'c' && dest[3] == 'd' && dest[4] == 'e' && dest[5] == '\0');
    dest[0] = '\0';
   
    static constexpr const wchar* const wide_src = L"de";
    wchar wide_dest[6] = { L'a', L'b', L'c', L'\0' };
    ASSERT_TRUE(CString::append_safe(wide_dest, 6, wide_src));
    ASSERT_TRUE(wide_dest[0] == L'a' && wide_dest[1] == L'b' && wide_dest[2] == L'c' && wide_dest[3] == L'd' && wide_dest[4] == L'e' && wide_dest[5] == L'\0');
    dest[0] = L'\0';

    // Thoses crash
    //ASSERT_FALSE(CString::append_safe(nullptr, 6, src));
    //ASSERT_FALSE(CString::append_safe(dest, 6, nullptr));
    //ASSERT_FALSE(CString::append_safe(nullptr, 6, wide_src));
    //ASSERT_FALSE(CString::append_safe(wide_dest, 6, nullptr));
    //ASSERT_FALSE(CString::append_safe((ansichar*)nullptr, 6, nullptr));
    //ASSERT_FALSE(CString::append_safe((wchar*)nullptr, 6, nullptr));
    //ASSERT_FALSE(CString::append_safe(dest, 1, src)); //  destination is not big enough
    //ASSERT_FALSE(CString::append_safe(wide_dest, 1, wide_src)); //  destination is not big enough
}

TEST(CString, append_partial) {
    using namespace hud;

    static constexpr const ansichar* const src = "de";
    ansichar dest[5] = { 'a', 'b', 'c', '\0' };
    ASSERT_TRUE(CString::append_partial(dest, src, 1) == dest);
    ASSERT_TRUE(dest[0] == 'a' && dest[1] == 'b' && dest[2] == 'c' && dest[3] == 'd' && dest[4] == '\0');

    static constexpr const wchar* const wide_src = L"de";
    wchar wide_dest[6] = { L'a', L'b', L'c', L'\0' };
    ASSERT_TRUE(CString::append_partial(wide_dest, wide_src, 1) == wide_dest);
    ASSERT_TRUE(wide_dest[0] == L'a' && wide_dest[1] == L'b' && wide_dest[2] == L'c' && wide_dest[3] == L'd' && wide_dest[4] == L'\0');

    // Thoses crash
    //ASSERT_FALSE(CString::append_partial(nullptr, src, 1));
    //ASSERT_FALSE(CString::append_partial(dest, nullptr, 1));
    //ASSERT_FALSE(CString::append_partial(nullptr, wide_src, 1));
    //ASSERT_FALSE(CString::append_partial(wide_dest, nullptr, 1));
    //ASSERT_FALSE(CString::append_partial((ansichar*)nullptr, nullptr, 1));
    //ASSERT_FALSE(CString::append_partial((wchar*)nullptr, nullptr, 1));
}

TEST(CString, append_partial_safe) {
    using namespace hud;

    static constexpr const ansichar* const src = "de";
    ansichar dest[6] = { 'a', 'b', 'c', '\0' };
    ASSERT_TRUE(CString::append_partial_safe(dest, 6, src, 1));
    ASSERT_TRUE(dest[0] == 'a' && dest[1] == 'b' && dest[2] == 'c' && dest[3] == 'd' && dest[4] == '\0');

    static constexpr const wchar* const wide_src = L"de";
    wchar wide_dest[6] = { L'a', L'b', L'c', L'\0' };
    ASSERT_TRUE(CString::append_partial_safe(wide_dest, 6, wide_src, 1));
    ASSERT_TRUE(wide_dest[0] == L'a' && wide_dest[1] == L'b' && wide_dest[2] == L'c' && wide_dest[3] == L'd' && wide_dest[4] == L'\0');
    
    //ASSERT_FALSE(CString::append_partial_safe(nullptr, 6, src, 1)); // destination is nullptr
    //ASSERT_FALSE(CString::append_partial_safe(dest, 6, nullptr, 1)); // source is nullptr
    //ASSERT_FALSE(CString::append_partial_safe(nullptr, 6, wide_src, 1)); // destination is nullptr
    //ASSERT_FALSE(CString::append_partial_safe(wide_dest, 6, nullptr, 1)); // source is nullptr
    //ASSERT_FALSE(CString::append_partial_safe((ansichar*)nullptr, 6, nullptr, 1)); // destination and source are nullptr
    //ASSERT_FALSE(CString::append_partial_safe((wchar*)nullptr, 6, nullptr, 1)); // destination and source are nullptr
    //ASSERT_FALSE(CString::append_partial_safe(dest, 0, src, 1)); // Buffer is too small
    //ASSERT_FALSE(CString::append_partial_safe(dest, 1, src, 1)); // Buffer is too small
    //ASSERT_FALSE(CString::append_partial_safe(wide_dest, 1, wide_src, 1)); // Buffer is too small
    //ASSERT_FALSE(CString::append_partial_safe(wide_dest, 0, wide_src, 1)); // Buffer is too small
}


TEST(CString, to_uppercase) {
    using namespace hud;

    ansichar txt[] = "abc123,;:!";
    ASSERT_TRUE(CString::to_uppercase(txt) == txt);
    ASSERT_TRUE(txt[0] == 'A' && txt[1] == 'B' && txt[2] == 'C' && txt[3] == '1' && txt[4] == '2' && txt[5] == '3' && txt[6] == ',' && txt[7] == ';' && txt[8] == ':' && txt[9] == '!' && txt[10] == '\0');
    wchar wide_txt[] = L"abc123,;:!";
    ASSERT_TRUE(CString::to_uppercase(wide_txt) == wide_txt);
    ASSERT_TRUE(wide_txt[0] == 'A' && wide_txt[1] == 'B' && wide_txt[2] == 'C' && wide_txt[3] == '1' && wide_txt[4] == '2' && wide_txt[5] == '3' && wide_txt[6] == ',' && wide_txt[7] == ';' && wide_txt[8] == ':' && wide_txt[9] == '!' && wide_txt[10] == '\0');
}

TEST(CString, to_uppercase_safe) {
    using namespace hud;

    ansichar txt[] = "abc123,;:!";
    ASSERT_TRUE(CString::to_uppercase_safe(txt, 10));
    ASSERT_TRUE(txt[0] == 'A' && txt[1] == 'B' && txt[2] == 'C' && txt[3] == '1' && txt[4] == '2' && txt[5] == '3' && txt[6] == ',' && txt[7] == ';' && txt[8] == ':' && txt[9] == '!' && txt[10] == '\0');
    ASSERT_FALSE(CString::to_uppercase_safe((ansichar*)nullptr, 11));
    ASSERT_FALSE(CString::to_uppercase_safe(txt, 0));
    ASSERT_FALSE(CString::to_uppercase_safe((ansichar*)nullptr, 0));

    wchar wide_txt[] = L"abc123,;:!";
    ASSERT_TRUE(CString::to_uppercase_safe(wide_txt, 10));
    ASSERT_TRUE(wide_txt[0] == 'A' && wide_txt[1] == 'B' && wide_txt[2] == 'C' && wide_txt[3] == '1' && wide_txt[4] == '2' && wide_txt[5] == '3' && wide_txt[6] == ',' && wide_txt[7] == ';' && wide_txt[8] == ':' && wide_txt[9] == '!' && wide_txt[10] == '\0');
    ASSERT_FALSE(CString::to_uppercase_safe((wchar*)nullptr, 11));
    ASSERT_FALSE(CString::to_uppercase_safe(wide_txt, 0));
    ASSERT_FALSE(CString::to_uppercase_safe((wchar*)nullptr, 0));

}

TEST(CString, to_uppercase_partial) {
    using namespace hud;

    ansichar txt[] = "abc123,;:!";
    ASSERT_TRUE(CString::to_uppercase_partial(txt, 2) == txt);
    ASSERT_TRUE(txt[0] == 'A' && txt[1] == 'B' && txt[2] == 'c' && txt[3] == '1' && txt[4] == '2' && txt[5] == '3' && txt[6] == ',' && txt[7] == ';' && txt[8] == ':' && txt[9] == '!' && txt[10] == '\0');
    wchar wide_txt[] = L"abc123,;:!";
    ASSERT_TRUE(CString::to_uppercase_partial(wide_txt, 2) == wide_txt);
    ASSERT_TRUE(wide_txt[0] == 'A' && wide_txt[1] == 'B' && wide_txt[2] == 'c' && wide_txt[3] == '1' && wide_txt[4] == '2' && wide_txt[5] == '3' && wide_txt[6] == ',' && wide_txt[7] == ';' && wide_txt[8] == ':' && wide_txt[9] == '!' && wide_txt[10] == '\0');
}

TEST(CString, to_uppercase_partial_safe) {
    using namespace hud;

    ansichar txt[] = "abc123,;:!";
    ASSERT_TRUE(CString::to_uppercase_partial_safe(txt, 10, 2));
    ASSERT_TRUE(txt[0] == 'A' && txt[1] == 'B' && txt[2] == 'c' && txt[3] == '1' && txt[4] == '2' && txt[5] == '3' && txt[6] == ',' && txt[7] == ';' && txt[8] == ':' && txt[9] == '!' && txt[10] == '\0');

    ASSERT_TRUE(CString::to_uppercase_partial_safe(txt, 10, 0));
    ASSERT_FALSE(CString::to_uppercase_partial_safe(txt, 10, 11));
    ASSERT_FALSE(CString::to_uppercase_partial_safe(txt, 12, 11));

    wchar wide_txt[] = L"abc123,;:!";
    ASSERT_TRUE(CString::to_uppercase_partial_safe(wide_txt, 10, 2));
    ASSERT_TRUE(wide_txt[0] == 'A' && wide_txt[1] == 'B' && wide_txt[2] == 'c' && wide_txt[3] == '1' && wide_txt[4] == '2' && wide_txt[5] == '3' && wide_txt[6] == ',' && wide_txt[7] == ';' && wide_txt[8] == ':' && wide_txt[9] == '!' && wide_txt[10] == '\0');

    ASSERT_TRUE(CString::to_uppercase_partial_safe(wide_txt, 10, 0));
    ASSERT_FALSE(CString::to_uppercase_partial_safe(wide_txt, 10, 11));
    ASSERT_FALSE(CString::to_uppercase_partial_safe(wide_txt, 12, 11));
}


TEST(CString, to_lowercase) {
    using namespace hud;

    ansichar txt[] = "ABC123,;:!";
    ASSERT_TRUE(CString::to_lowercase(txt) == txt);
    ASSERT_TRUE(txt[0] == 'a' && txt[1] == 'b' && txt[2] == 'c' && txt[3] == '1' && txt[4] == '2' && txt[5] == '3' && txt[6] == ',' && txt[7] == ';' && txt[8] == ':' && txt[9] == '!' && txt[10] == '\0');
    wchar wide_txt[] = L"ABC123,;:!";
    ASSERT_TRUE(CString::to_lowercase(wide_txt) == wide_txt);
    ASSERT_TRUE(wide_txt[0] == 'a' && wide_txt[1] == 'b' && wide_txt[2] == 'c' && wide_txt[3] == '1' && wide_txt[4] == '2' && wide_txt[5] == '3' && wide_txt[6] == ',' && wide_txt[7] == ';' && wide_txt[8] == ':' && wide_txt[9] == '!' && wide_txt[10] == '\0');
}

TEST(CString, to_lowercase_safe) {
    using namespace hud;

    ansichar txt[] = "ABC123,;:!";
    ASSERT_TRUE(CString::to_lowercase_safe(txt, 10));
    ASSERT_TRUE(txt[0] == 'a' && txt[1] == 'b' && txt[2] == 'c' && txt[3] == '1' && txt[4] == '2' && txt[5] == '3' && txt[6] == ',' && txt[7] == ';' && txt[8] == ':' && txt[9] == '!' && txt[10] == '\0');
    ASSERT_FALSE(CString::to_lowercase_safe((ansichar*)nullptr, 11));
    ASSERT_FALSE(CString::to_lowercase_safe(txt, 0));
    ASSERT_FALSE(CString::to_lowercase_safe((ansichar*)nullptr, 0));

    wchar wide_txt[] = L"ABC123,;:!";
    ASSERT_TRUE(CString::to_lowercase_safe(wide_txt, 10));
    ASSERT_TRUE(wide_txt[0] == 'a' && wide_txt[1] == 'b' && wide_txt[2] == 'c' && wide_txt[3] == '1' && wide_txt[4] == '2' && wide_txt[5] == '3' && wide_txt[6] == ',' && wide_txt[7] == ';' && wide_txt[8] == ':' && wide_txt[9] == '!' && wide_txt[10] == '\0');
    ASSERT_FALSE(CString::to_lowercase_safe((wchar*)nullptr, 11));
    ASSERT_FALSE(CString::to_lowercase_safe(wide_txt, 0));
    ASSERT_FALSE(CString::to_lowercase_safe((wchar*)nullptr, 0));
}

TEST(CString, to_lowercase_partial) {
    using namespace hud;

    ansichar txt[] = "ABC123,;:!";
    ASSERT_TRUE(CString::to_lowercase_partial(txt, 2) == txt);
    ASSERT_TRUE(txt[0] == 'a' && txt[1] == 'b' && txt[2] == 'C' && txt[3] == '1' && txt[4] == '2' && txt[5] == '3' && txt[6] == ',' && txt[7] == ';' && txt[8] == ':' && txt[9] == '!' && txt[10] == '\0');

    wchar wide_txt[] = L"ABC123,;:!";
    ASSERT_TRUE(CString::to_lowercase_partial(wide_txt, 2) == wide_txt);
    ASSERT_TRUE(wide_txt[0] == 'a' && wide_txt[1] == 'b' && wide_txt[2] == 'C' && wide_txt[3] == '1' && wide_txt[4] == '2' && wide_txt[5] == '3' && wide_txt[6] == ',' && wide_txt[7] == ';' && wide_txt[8] == ':' && wide_txt[9] == '!' && wide_txt[10] == '\0');
}

TEST(CString, to_lowercase_partial_safe) {
    using namespace hud;

    ansichar txt[] = "ABC123,;:!";
    ASSERT_TRUE(CString::to_lowercase_partial_safe(txt, 10, 2));
    ASSERT_TRUE(txt[0] == 'a' && txt[1] == 'b' && txt[2] == 'C' && txt[3] == '1' && txt[4] == '2' && txt[5] == '3' && txt[6] == ',' && txt[7] == ';' && txt[8] == ':' && txt[9] == '!' && txt[10] == '\0');

    ASSERT_TRUE(CString::to_lowercase_partial_safe(txt, 10, 0));
    ASSERT_FALSE(CString::to_lowercase_partial_safe(txt, 10, 11));
    ASSERT_FALSE(CString::to_lowercase_partial_safe(txt, 12, 11));

    wchar wide_txt[] = L"ABC123,;:!";
    ASSERT_TRUE(CString::to_lowercase_partial_safe(wide_txt, 10, 2));
    ASSERT_TRUE(wide_txt[0] == 'a' && wide_txt[1] == 'b' && wide_txt[2] == 'C' && wide_txt[3] == '1' && wide_txt[4] == '2' && wide_txt[5] == '3' && wide_txt[6] == ',' && wide_txt[7] == ';' && wide_txt[8] == ':' && wide_txt[9] == '!' && wide_txt[10] == '\0');

    ASSERT_TRUE(CString::to_lowercase_partial_safe(wide_txt, 10, 0));
    ASSERT_FALSE(CString::to_lowercase_partial_safe(wide_txt, 10, 11));
    ASSERT_FALSE(CString::to_lowercase_partial_safe(wide_txt, 12, 11));
}

TEST(CString, equals) {
    using namespace hud;

    ASSERT_TRUE(CString::equals("abc", "abc"));
    ASSERT_FALSE(CString::equals("aBc", "abc"));
    ASSERT_FALSE(CString::equals("abc", "ab"));
    ASSERT_TRUE(CString::equals(L"abc", L"abc"));
    ASSERT_FALSE(CString::equals(L"aBc", L"abc"));
    ASSERT_FALSE(CString::equals(L"abc", L"ab"));
}

TEST(CString, equals_partial) {
    using namespace hud;

    ASSERT_TRUE(CString::equals_partial("abc", "abc", 1));
    ASSERT_FALSE(CString::equals_partial("abc", "bc", 2));
    ASSERT_FALSE(CString::equals_partial("aBc", "abc", 3));
    ASSERT_TRUE(CString::equals_partial("aBc", "abc", 1));


    ASSERT_TRUE(CString::equals_partial(L"abc", L"abc", 1));
    ASSERT_FALSE(CString::equals_partial(L"abc", L"bc", 2));
    ASSERT_FALSE(CString::equals_partial(L"aBc", L"abc", 3));
    ASSERT_TRUE(CString::equals_partial(L"aBc", L"abc", 1));
}

TEST(CString, length) {
    using namespace hud;

    ASSERT_TRUE(CString::length("aBc") == 3);
    ASSERT_TRUE(CString::length(L"aBc") == 3);
    ASSERT_FALSE(CString::length("aBcd") == 3);
    ASSERT_FALSE(CString::length(L"aBcd") == 3);
}

TEST(CString, length_safe) {
    using namespace hud;

    ASSERT_TRUE(CString::length_safe("aBc", 3) == 3);
    ASSERT_TRUE(CString::length_safe("aBc", 2) == 2);
    ASSERT_TRUE(CString::length_safe("aBc", 4) == 3);
    ASSERT_TRUE(CString::length_safe((ansichar*)nullptr, 2) == 0);

    ASSERT_TRUE(CString::length_safe(L"aBc", 3) == 3);
    ASSERT_TRUE(CString::length_safe(L"aBc", 2) == 2);
    ASSERT_TRUE(CString::length_safe(L"aBc", 4) == 3);
    ASSERT_TRUE(CString::length_safe((wchar*)nullptr, 2) == 0);
}

TEST(CString, find_string) {
    using namespace hud;

    const ansichar* str = "abcdefcd";
    ASSERT_TRUE(CString::find_string(str, "cd") == str + 2);
    ASSERT_TRUE(CString::find_string(str, "fe") == nullptr);

    const wchar* wide_str = L"abcdef";
    ASSERT_TRUE(CString::find_string(wide_str, L"cd") == wide_str + 2);
    ASSERT_TRUE(CString::find_string(wide_str, L"fe") == nullptr);
}

TEST(CString, find_character) {
    using namespace hud;

    const ansichar* str = "abcdefcd";
    ASSERT_TRUE(CString::find_character(str, 'c') == str + 2);
    ASSERT_TRUE(CString::find_character(str, 'g') == nullptr);

    const wchar* wide_str = L"abcdef";
    ASSERT_TRUE(CString::find_character(wide_str, 'c') == wide_str + 2);
    ASSERT_TRUE(CString::find_character(wide_str, 'g') == nullptr);
}

TEST(CString, format_vargs) {
    using namespace hud;

    const ansichar* fmt = "Hello %s! %ls time";
    ansichar buffer[256];
    i32 character_count = HUD_TEST::call_format_vargs(buffer, 256, fmt, "World", L"Hammer");
    ASSERT_TRUE(CString::equals(buffer, "Hello World! Hammer time"));
    ASSERT_TRUE(character_count == 24);

    const wchar* wide_fmt = L"Hello %ls! %ls time";
    wchar wide_buffer[256];
    character_count = HUD_TEST::call_format_vargs(wide_buffer, 256, wide_fmt, L"World", L"Hammer");
    ASSERT_TRUE(CString::equals(wide_buffer, L"Hello World! Hammer time"));
    ASSERT_TRUE(character_count == 24);
}

TEST(CString, format) {
    using namespace hud;

    const ansichar* fmt = "Hello %s! %ls time";
    ansichar buffer[256];
    i32 character_count = CString::format(buffer, 256, fmt, "World", L"Hammer");
    ASSERT_TRUE(CString::equals(buffer, "Hello World! Hammer time"));
    ASSERT_TRUE(character_count == 24);

    const wchar* wide_fmt = L"Hello %ls! %ls time";
    wchar wide_buffer[256];
    character_count = CString::format(wide_buffer, 256, wide_fmt, L"World", L"Hammer");
    ASSERT_TRUE(CString::equals(wide_buffer, L"Hello World! Hammer time"));
    ASSERT_TRUE(character_count == 24);
}