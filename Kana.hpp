#pragma once
#include <QStringList>
#include <vector>


enum Phonetics {
    C           = 1 << 0,   // consonant   согласная
    V           = 1 << 1,   // vowel       гласная
    CV          = 1 << 2,   // consonant + vowel
    SmallTSU    = 1 << 3,
    N           = 1 << 4,

    NONE        = 1 << 7
};

enum SymbolEnum {
    Hiragana = 0,
    Katakana,
    PhoneticsENG,
    PhoneticsRUS
};

struct Symbol {
    Phonetics   phonetics;
    QStringList text;
};
using SymVec = std::vector<Symbol>;

static const QChar DoubleVowelSign = ':';
//static const Symbol LongVowel       = {Phonetics::V, {"ー"}}
static Symbol   LongConsonant   = {Phonetics::SmallTSU, {"っ", "ッ", "|", "|"}};
static Symbol   NN              = {Phonetics::N, {"ん", "ン", "nn", "нн"}};

static QString  shi_eng = "shi";    // si
static QString  shi_rus = "ши";     // си

static QString  chi_eng = "chi";    // di
static QString  chi_rus = "чи";     // дзи
static QString  di_eng  = "di";
static QString  di_rus  = "ди";

static QString  tsu_eng = "tsu";    // tu
static QString  tsu_rus = "цу";     // дзу
static QString  du_eng  = "du";
static QString  du_rus  = "ду";




static SymVec Column1 =
{{
    {Phonetics::V, {"あ", "ア", "a", "а"}},
    {Phonetics::V, {"い", "イ", "i", "и"}},
    {Phonetics::V, {"う", "ウ", "u", "у"}},
    {Phonetics::V, {"え", "エ", "e", "э"}},
    {Phonetics::V, {"お", "オ", "o", "о"}}
}};

static SymVec Column2_K =
{{
    {Phonetics::CV, {"か", "カ", "ka", "ка"}},
    {Phonetics::CV, {"き", "キ", "ki", "ки"}},
    {Phonetics::CV, {"く", "ク", "ku", "ку"}},
    {Phonetics::CV, {"け", "ケ", "ke", "кэ"}},
    {Phonetics::CV, {"こ", "コ", "ko", "ко"}}
}};

static SymVec Column2_G =
{{
    {Phonetics::CV, {"が", "ガ", "ga", "га"}},
    {Phonetics::CV, {"ぎ", "ギ", "gi", "ги"}},
    {Phonetics::CV, {"ぐ", "グ", "gu", "гу"}},
    {Phonetics::CV, {"げ", "ゲ", "ge", "гэ"}},
    {Phonetics::CV, {"ご", "ゴ", "go", "го"}}
}};

static SymVec Column3_S =
{{
    {Phonetics::CV, {"さ", "サ", "sa", "са"}},
    {Phonetics::CV, {"し", "シ", shi_eng, shi_rus}},
    {Phonetics::CV, {"す", "ス", "su", "су"}},
    {Phonetics::CV, {"せ", "セ", "se", "сэ"}},
    {Phonetics::CV, {"そ", "ソ", "so", "со"}}
}};

static SymVec Column3_Z =
{{
    {Phonetics::CV, {"ざ", "ザ", "za", "дза"}},
    {Phonetics::CV, {"じ", "ジ", "zi", "дзи"}},
    {Phonetics::CV, {"ず", "ズ", "zu", "дзу"}},
    {Phonetics::CV, {"ぜ", "ズ", "ze", "дзэ"}},
    {Phonetics::CV, {"ぞ", "ゾ", "zo", "дзо"}}
}};

static SymVec Column4_T =
{{
    {Phonetics::CV, {"た", "タ", "ta", "та"}},
    {Phonetics::CV, {"ち", "チ", chi_eng, chi_rus}},
    {Phonetics::CV, {"つ", "ツ", du_eng, du_rus}},
    {Phonetics::CV, {"て", "テ", "te", "тэ"}},
    {Phonetics::CV, {"と", "テ", "to", "то"}}
}};

static SymVec Column4_D =
{{
    {Phonetics::CV, {"だ", "ダ", "da", "да"}},
    {Phonetics::CV, {"ぢ", "ヂ", di_eng, di_rus}},
    {Phonetics::CV, {"づ", "ヅ", tsu_eng, tsu_rus}},
    {Phonetics::CV, {"で", "デ", "de", "дэ"}},
    {Phonetics::CV, {"ど", "ド", "do", "до"}}
}};

static SymVec Column5_N =
{{
    {Phonetics::CV, {"な", "ナ", "na", "на"}},
    {Phonetics::CV, {"に", "ニ", "ni", "ни"}},
    {Phonetics::CV, {"ぬ", "ヌ", "nu", "ну"}},
    {Phonetics::CV, {"ね", "ネ", "ne", "нэ"}},
    {Phonetics::CV, {"の", "ノ", "no", "но"}}
}};

static SymVec Column6_H =
{{
    {Phonetics::CV, {"は", "ハ", "ha", "ха"}},
    {Phonetics::CV, {"ひ", "ヒ", "hi", "хи"}},
    {Phonetics::CV, {"ふ", "フ", "fu", "фу"}},
    {Phonetics::CV, {"へ", "ヘ", "he", "хэ"}},
    {Phonetics::CV, {"ほ", "ホ", "ho", "хо"}}
}};

static SymVec Column6_B =
{{
    {Phonetics::CV, {"ば", "バ", "ba", "ба"}},
    {Phonetics::CV, {"び", "ビ", "bi", "би"}},
    {Phonetics::CV, {"ぶ", "ブ", "bu", "бу"}},
    {Phonetics::CV, {"べ", "ボ", "be", "бэ"}},
    {Phonetics::CV, {"ぼ", "ベ", "bo", "бо"}}
}};

static SymVec Column6_P =
{{
    {Phonetics::CV, {"ぱ", "パ", "pa", "па"}},
    {Phonetics::CV, {"ぴ", "ピ", "pi", "пи"}},
    {Phonetics::CV, {"ぷ", "プ", "pu", "пу"}},
    {Phonetics::CV, {"ぺ", "ポ", "pe", "пэ"}},
    {Phonetics::CV, {"ぽ", "ペ", "po", "по"}}
}};
