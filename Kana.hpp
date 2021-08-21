#pragma once
#include <QChar>
#include <QStringList>
#include <array>
#include <vector>


enum Phonetics {
    C           = 1 << 0,      // consonant   согласная
    V           = 1 << 1,      // vowel       гласная
    SmallTSU    = 1 << 2,
    N           = 1 << 3,

    CV = C | V       // consonant + vowel
};

enum SymbolEnum {
    Hiragana = 0,
    Katakana = 1,
    PhoneticsENG = 2,
    PhoneticsRUS = 3
};

struct Symbol {
    const Phonetics phonetic;
    QStringList     text;
};

//static const Symbol LongVowel       = {Phonetics::V, {"ー"}}
static Symbol   LongConsonant   = {Phonetics::SmallTSU, {"っ", "ッ", "", ""}};
static Symbol   NN              = {Phonetics::N, {"ん", "ン", "n", "н"}};

static QString  shi_eng = "shi";    // si
static QString  shi_rus = "ши";     // си
static QString  chi_eng = "chi";    // di
static QString  chi_rus = "чи";     // дзи
static QString  tsu_eng = "tsu";    // tu
static QString  tsu_rus = "цу";     // дзу




static std::vector<Symbol> Column1 =
{{
    {Phonetics::V, {"あ", "ア", "a", "а"}},
    {Phonetics::V, {"い", "イ", "i", "и"}},
    {Phonetics::V, {"う", "ウ", "u", "у"}},
    {Phonetics::V, {"え", "エ", "e", "э"}},
    {Phonetics::V, {"お", "オ", "o", "о"}}
}};

static std::vector<Symbol> Column2_K =
{{
    {Phonetics::CV, {"か", "カ", "ka", "ка"}},
    {Phonetics::CV, {"き", "キ", "ki", "ки"}},
    {Phonetics::CV, {"く", "ク", "ku", "ку"}},
    {Phonetics::CV, {"け", "ケ", "ke", "кэ"}},
    {Phonetics::CV, {"こ", "コ", "ko", "ко"}}
}};

static std::vector<Symbol> Column2_G =
{{
    {Phonetics::CV, {"が", "ガ", "ga", "га"}},
    {Phonetics::CV, {"ぎ", "ギ", "gi", "ги"}},
    {Phonetics::CV, {"ぐ", "グ", "gu", "гу"}},
    {Phonetics::CV, {"げ", "ゲ", "ge", "гэ"}},
    {Phonetics::CV, {"ご", "ゴ", "go", "го"}}
}};

static std::vector<Symbol> Column3_S =
{{
    {Phonetics::CV, {"さ", "サ", "sa", "са"}},
    {Phonetics::CV, {"し", "シ", shi_eng, shi_rus}},
    {Phonetics::CV, {"す", "ス", "su", "су"}},
    {Phonetics::CV, {"せ", "セ", "se", "сэ"}},
    {Phonetics::CV, {"そ", "ソ", "so", "со"}}
}};

static std::vector<Symbol> Column3_Z =
{{
    {Phonetics::CV, {"ざ", "ザ", "za", "дза"}},
    {Phonetics::CV, {"じ", "ジ", "zi", "дзи"}},
    {Phonetics::CV, {"ず", "ズ", "zu", "дзу"}},
    {Phonetics::CV, {"ぜ", "ズ", "ze", "дзэ"}},
    {Phonetics::CV, {"ぞ", "ゾ", "zo", "дзо"}}
}};

static std::vector<Symbol> Column4_T =
{{
    {Phonetics::CV, {"た", "タ", "ta", "та"}},
    {Phonetics::CV, {"ち", "チ", chi_eng, chi_rus}},
    {Phonetics::CV, {"つ", "ツ", tsu_eng, tsu_rus}},
    {Phonetics::CV, {"て", "テ", "te", "тэ"}},
    {Phonetics::CV, {"と", "テ", "to", "то"}}
}};

static std::vector<Symbol> Column4_D =
{{
    {Phonetics::CV, {"だ", "ダ", "da", "да"}},
    {Phonetics::CV, {"ぢ", "ヂ", chi_eng, chi_rus}},
    {Phonetics::CV, {"づ", "ヅ", tsu_eng, tsu_rus}},
    {Phonetics::CV, {"で", "デ", "de", "дэ"}},
    {Phonetics::CV, {"ど", "ド", "do", "до"}}
}};

static std::vector<Symbol> Column5_N =
{{
    {Phonetics::CV, {"な", "ナ", "na", "на"}},
    {Phonetics::CV, {"に", "ニ", "ni", "ни"}},
    {Phonetics::CV, {"ぬ", "ヌ", "nu", "ну"}},
    {Phonetics::CV, {"ね", "ネ", "ne", "нэ"}},
    {Phonetics::CV, {"の", "ノ", "no", "но"}}
}};

static std::vector<Symbol> Column6_H =
{{
    {Phonetics::CV, {"は", "ハ", "ha", "ха"}},
    {Phonetics::CV, {"ひ", "ヒ", "hi", "хи"}},
    {Phonetics::CV, {"ふ", "フ", "fu", "фу"}},
    {Phonetics::CV, {"へ", "ヘ", "he", "хэ"}},
    {Phonetics::CV, {"ほ", "ホ", "ho", "хо"}}
}};

static std::vector<Symbol> Column6_B =
{{
    {Phonetics::CV, {"ば", "バ", "ba", "ба"}},
    {Phonetics::CV, {"び", "ビ", "bi", "би"}},
    {Phonetics::CV, {"ぶ", "ブ", "bu", "бу"}},
    {Phonetics::CV, {"べ", "ボ", "be", "бэ"}},
    {Phonetics::CV, {"ぼ", "ベ", "bo", "бо"}}
}};

static std::vector<Symbol> Column6_P =
{{
    {Phonetics::CV, {"ぱ", "パ", "pa", "па"}},
    {Phonetics::CV, {"ぴ", "ピ", "pi", "пи"}},
    {Phonetics::CV, {"ぷ", "プ", "pu", "пу"}},
    {Phonetics::CV, {"ぺ", "ポ", "pe", "пэ"}},
    {Phonetics::CV, {"ぽ", "ペ", "po", "по"}}
}};
