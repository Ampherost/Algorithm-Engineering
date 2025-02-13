#include <string>
#include <vector>

std::vector<std::string> guesses(unsigned known) {
  std::vector<std::string> response {
   "000000",
   "111111",
   "121212",
   "222222",
   "333333",
   "444444",
   "555555",
   "666666",
   "777777",
   "888888",
   "999999",
   "123456",
   "654321",
   "aaaaaa",
   "bbbbbb",
   "cccccc",
   "dddddd",
   "ffffff",
   "gggggg",
   "hhhhhh",
   "jjjjjj",
   "kkkkkk",
   "llllll",
   "mmmmmm",
   "oooooo",
   "pppppp",
   "qqqqqq",
   "ssssss",
   "tttttt",
   "wwwwww",
   "xxxxxx",
   "yyyyyy",
   "zzzzzz",
   "cheese",
   "potato",
   "qwerty",
   "asdfgh",
   "zxcvbn",
   "abcdef",
   "zyxwvu",
   "miller",
   "oliver",
   "elijah",
   "daniel",
   "samuel",
   "joseph",
   "123123",
   "qweasd",
   "abc123",
   "dragon",
   "monkey",
   "696969",
   "shadow",
   "master",
   "123321",
   "qazwsx",
   "123qwe",
   "killer",
   "ashley",
   "bailey",
   "flower",
   "jordan",
   "harley",
   "ranger",
   "buster",
   "summer",
   "batman",
   "hottie",
   "loveme",
   "maggie",
   "secret",
   "q1w2e3",
   "1q2w3e",
   "lovely",
   "hannah",
   "sophie",
   "amanda",
   "111222",
   "222333",
   "333444",
   "444555",
   "555666",
   "666777",
   "777888",
   "888999",
   "112233",
   "445566",
   "556677",
   "667788",
   "778899",
   "010101",
   "999888",
   "777666",
   "888777",
   "159753",
   "753951",
   "147258",
   "258369",
   "369258",
   "987654",
   "456789",
   "234567",
   "765432",
   "654987",
   "102030",
   "112358",
   "314159",
   "161616",
   "828282",
   "121314",
   "232323",
   "343434",
   "454545",
   "565656",
   "676767",
   "787878",
   "898989",
   "909090",
   "808080",
   "707070",
   "505050",
   "404040",
   "303030",
   "202020",
   "131313",
   "141414",
   "151515",
   "171717",
   "181818",
   "191919",
   "212121",
   "242424",
   "252525",
   "262626",
   "272727",
   "282828",
   "292929",
   "313131",
   "323232",
   "333666",
   "444777",
   "555888",
   "666999",
   "777000",
   "888111",
   "999222"

   "passwd",  // 1
    "adm123",  // 2
    "qwe123",  // 3
    "pass12",  // 4
    "abcxyz",  // 5
    "qaz123",  // 6
    "zxc123",  // 7
    "mypass",  // 8
    "ilovey",  // 9
    "s3cr3t",  // 10
    "login1",  // 11
    "sun123",  // 12
    "star12",  // 13
    "money1",  // 14
    "ninja1",  // 15
    "eagle1",  // 16
    "orange",  // 17
    "purple",  // 18
    "silver",  // 19
    "golden",  // 20
    "cookie",  // 21
    "winter",  // 22
    "spring",  // 23
    "autumn",  // 24
    "soccer",  // 25
    "hockey",  // 26
    "tennis",  // 27
    "banana",  // 28
    "cherry",  // 29
    "peachy",  // 30
    "muffin",  // 31
    "kitten",  // 32
    "puppy1",  // 33
    "scooby",  // 34
    "101010",  // 35
    "555000",  // 36
    "246810",  // 37
    "135790",  // 38
    "975310",  // 39
    "864200",  // 40
    "112244",  // 41
    "223355",  // 42
    "334466",  // 43
    "445577",  // 44
    "556688",  // 45
    "667799",  // 46
    "778800",  // 47
    "889911",  // 48
    "990011",  // 49
    "141516",  // 50
    "161718",  // 51
    "181920",  // 52
    "202122",  // 53
    "232425",  // 54
    "252627",  // 55
    "272829",  // 56
    "303132",  // 57
    "333435",  // 58
    "363738",  // 59
    "394041",  // 60
    "424344",  // 61
    "454647",  // 62
    "484950",  // 63
    "515253",  // 64
    "545556",  // 65
    "575859",  // 66
    "606162",  // 67
    "636465",  // 68
    "666768",  // 69
    "696972",  // 70
    "727374",  // 71
    "757677",  // 72
    "787980",  // 73
    "818283",  // 74
    "848586",  // 75
    "878889",  // 76
    "909192",  // 77
    "939495",  // 78
    "969798",  // 79
    "991001",  // 80
    "a1b2c3",  // 81
    "c3b2a1",  // 82
    "abc111",  // 83
    "111abc",  // 84
    "xyz789",  // 85
    "789xyz",  // 86
    "love12",  // 87
    "passme",  // 88
    "qwert7",  // 89
    "asdf12",  // 90
    "zxcv12",  // 91
    "admin2",  // 92
    "root12",  // 93
    "user01",  // 94
    "guest1",  // 95
    "000111",  // 96
    "222111",  // 97
    "333222",  // 98
    "444333",  // 99
    "555444"   // 100
    "qwer12",
    "abcd12",
    "passw1",
    "admin1",
    "user12",
    "guest2",
    "hello1",
    "world1",
    "sunset",
    "butter",
    "lkjhgf",
    "hacker",
    "guitar",
    "donald",
    "ginger",
    "matrix",
    "toyota",
    "mercur",
    "chevy1",
    "ferris",
    "pepper",
    "sugar1",
    "coffee",
    "bottle",
    "tomato",
    "salmon",
    "violet",
    "indigo",
    "maroon",
    "bronze",
    "sierra",
    "raptor",
    "falcon",
    "tiger1",
    "lion12",
    "cheeta",
    "zombie",
    "spider",
    "hunter",
    "robber",
    "pirate",
    "samson",
    "nights",
    "dawn12",
    "eclips",
    "frozen",
    "thnder",
    "lightn",
    "storm1",
    "alpha1",
    "beta12",
    "gamma1",
    "delta1",
    "theta1",
    "omega1",
    "sigma1",
    "zeta12",
    "eta123",
    "novice",
    "wizard",
    "muggle",
    "hobbit",
    "frodo1",
    "bilbo1",
    "gandlf",
    "legola",
    "rohani",
    "shire1",
    "sniper",
    "tunnel",
    "copper",
    "throne",
    "castle",
    "forest",
    "danger",
    "insane",
    "bullet",
    "rocket",
    "viking",
    "safari",
    "jungle",
    "desert",
    "marine",
    "piracy",
    "doctor",
    "nuking",
    "thirst",
    "bomber",
    "cancer",
    "pistol",
    "hammer",
    "sneaky",
    "silent",
    "prince",
    "king12",
    "queen1",
    "power1",
    "lancer",
    "strike",
    "attack"
  
  };
  
  return response;
}