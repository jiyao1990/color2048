//
//  Global.cpp
//  CppGame
//
//  Created by Jiyao on 15/1/30.
//
//

#include "Global.h"
#include "Interface.h"
#include "jsons.h"
#include "GameMap.h"

#pragma mark -
#pragma mark SGJsonPair

JsonPair::JsonPair(string key, string value)
{
    m_key = key;
    m_value = value;
}

JsonPair::JsonPair()
{
    
}

JsonPair* JsonPair::create(string key, string value)
{
    JsonPair* pRet = new JsonPair(key, value);
    if (pRet)
    {
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;
}


#pragma mark -
#pragma mark Global

Global* Global::_instance = NULL;

Color4B Global::colorMap[colorType_Size][maxLevel] ={
    
    {
        Color4B(240, 255, 200, 255),
        Color4B(180, 245, 180, 255),
        Color4B(150, 220, 120, 255),
        Color4B(110, 200, 100, 255),
        Color4B(80,  175, 70,  255),
        Color4B(40,  145, 50,  255),
        Color4B(25,  115, 25,  255),
        Color4B(15,  90,  15,  255),
        Color4B(10,  60,  10,  255),
        Color4B(0,   30,  0,   255),
        Color4B(0,   0,   0,   255),
    },
    {
        Color4B(143, 244, 255, 255),
        Color4B(100, 205, 225, 255),
        Color4B(75,  172, 205, 255),
        Color4B(65,  150, 175, 255),
        Color4B(55,  130, 155, 255),
        Color4B(46,  106, 125, 255),
        Color4B(25,  80,  105, 255),
        Color4B(27,  60,  74,  255),
        Color4B(10,  40,  55,  255),
        Color4B(0,   10,  30,  255),
        Color4B(0,   0,   0,   255)
    },
    {
        Color4B(254, 190, 191, 255),
        Color4B(252, 119, 142, 255),
        Color4B(240, 80,  100, 255),
        Color4B(220, 60,  70,  255),
        Color4B(200, 40,  50,  255),
        Color4B(187, 17,  24,  255),
        Color4B(155, 15,  20,  255),
        Color4B(113, 12,  15,  255),
        Color4B(55,  10,  10,  255),
        Color4B(30,  0,   0,   255),
        Color4B(0,   0,   0,   255)},
};

string Global::shareText1[] =
{
    "我卡在月球上",
    "我钻在火星上",
    "我抱着太阳",
    INVALID_VALUE_STR,
    "我和天才小熊猫一起",
    "我和江宁婆婆一起",
    "我和邓超一起",
    "我和马建国一起",
    "我和使徒子一起",
    "我抱着王尼玛",
    "我举着王大锤",
    "我看着小马达",
    "我搂着所长",
    "我拉着韩寒",
    INVALID_VALUE_STR,
    "我思念着阿部高和",
    "我陪着黑猫警长",
    "我凝视着喜洋洋",
    "我亲吻着阿尔托利亚",
    "我和麻仓叶王",
    "我在卡卡西身上",
    "我在初音怀里",
    "我在大白肚子上",
    "我在路飞头上",
    "我在葫芦娃手里",
    "我摸着星矢",
    "我思念着贝吉塔",
    INVALID_VALUE_STR,
    "我蹲在沙发上",
    "我被绑在床上",
    "我站在凳子上",
    "我坐在桌子上",
    "我藏在柜子里",
    "我在办公室",
    "我在电梯里",
    "我在餐厅里",
    "我潜在澡堂里",
    INVALID_VALUE_STR,
    "我在大广场",
    "我蹲在树上",
    "我躺在海底",
    "我爬在地上",
    "我漂在海上",
    "我在马路边",
    INVALID_VALUE_STR,
    "我倒立在楼顶上",
    "我在朋友家里",
    "我在女友家里",
    "我在火车上",
    "我在飞机上",
    INVALID_VALUE_STR,
    "我在男友家里",
    "我在老师家里",
    "我在老板家里",
    "我在厕所里",
    "我在教室里",
    INVALID_VALUE_STR,
    "我坐在粪坑前",
    "我躺在花丛中",
    "我卡在麦垛中",
    "我插在土堆里",
    "我和鲁鲁修一起",
    INVALID_VALUE_STR,
    "我站在垃圾桶里",
    "我摸着猫口三三",
    "我看着炮姐胖次",
    "我拉着大头儿子",
    INVALID_VALUE_STR,
    "我坐在银桑肩上",
    "我被三笠抱着",
    "我抱着哆啦A梦",
    "我抱着皮卡丘",
    INVALID_VALUE_STR,
    "我在作者家里",
    "我在作者身上",
    "我在作者怀里",
    INVALID_VALUE_STR,
    "我在作者头上",
    "我和作者一起",
    INVALID_VALUE_STR,
};

string Global::shareText1_en[] = {
    
    "I killed",
    "I rubbed",
    "I liked",
    "I smoked",
    INVALID_VALUE_STR,
    "I pulled out",
    "I forgive",
    "I bit",
    "I annoyed",
    "I attacked",
    "I baked",
    "I beat",
    "I beged",
    "I blowed",
    "I bothered",
    INVALID_VALUE_STR,
    "I brushed",
    "I burnt",
    "I buried",
    "I bought",
    "I eated",
    "I called",
    "I kissed",
    "I carried",
    "I cheered",
    INVALID_VALUE_STR,
    "I steped on",
    "I licked",
    "I played",
    "I stealed",
    "I cooked",
    "I copied",
    "I cuted",
    "I cured",
    "I damaged",
    INVALID_VALUE_STR,
    "I laughed at",
    "I spit",
    "I fall in love with",
    "I kicked",
    "I brought",
    "I destroyed",
    "I dug",
    "I fucked",
    "I ride",
    INVALID_VALUE_STR,
    "I discoveried",
    "I did",
    "I drank",
    "I draw",
    "I drown",
    "I enjoy",
    "I envied",
    "I punish",
    "I push",
    "I pull",
    INVALID_VALUE_STR,
    "I fetched",
    "I feed",
    "I find",
    "I looked at",
    "I fill",
    "I forgot",
    "I freeze",
    "I protect",
    INVALID_VALUE_STR,
    "I fry",
    "I gain",
    "I get",
    "I give",
    "I grow",
    "I hear",
    "I press",
    INVALID_VALUE_STR,
    "I help",
    "I hold",
    "I hurt",
    "I joke",
    "I knock",
    "I recall",
    INVALID_VALUE_STR,
    "I lead",
    "I liberate",
    "I lay",
    "I lift",
    "I cosplay",
    "I point",
    INVALID_VALUE_STR,
    "I make love",
    "I marry",
    "I mend",
    "I miss",
    "I pick",
    "I place",
    INVALID_VALUE_STR,
    "I nail",
    "I need",
    "I open",
    "I paint",
    INVALID_VALUE_STR,
};

string Global::shareText2[] = {
    
    "满心欢喜地",
    "迫不及待地",
    "心情舒畅地",
    INVALID_VALUE_STR,
    "心软地",
    "华丽丽地",
    "猛地",
    "duang地一下",
    "啪地一下",
    "萌萌哒",
    "默然地",
    "果断地",
    "犹豫不决地",
    "心塞地",
    "淫荡地",
    INVALID_VALUE_STR,
    "腹黑地",
    "冷血无情地",
    "变态地",
    "抖S地",
    "傲娇地",
    "开着外挂般地",
    "苦逼地",
    "撸着",
    "任劳任怨地",
    "心满意足地",
    INVALID_VALUE_STR,
    "神经兮兮地",
    "满脸通红地",
    "偷偷摸摸地",
    "歇斯底里地",
    "不可理喻地",
    "哈哈大笑着",
    INVALID_VALUE_STR,
    "偷奸耍滑地",
    "莫名其妙地",
    "心照不宣地",
    "神经病般地",
    "兴高采烈地",
    INVALID_VALUE_STR,
    "美美哒",
    "看着神经病般地",
    "摸着大腿",
    "笑嘻嘻地",
    "中二病般地",
    INVALID_VALUE_STR,
    "潇洒地",
    "无语地",
    "胡乱地",
    "疯狂地",
    "傻笑着",
    INVALID_VALUE_STR,
    "邪恶地",
    "痛哭着",
    "面瘫着",
    "冷笑着",
    "摸着胸口",
    "搓着手",
    INVALID_VALUE_STR,
    "小心地",
    "慢悠悠地",
    "冷漠地",
    "心疼地",
    INVALID_VALUE_STR,
    "害怕地",
    "安安静静地",
    "舒舒服服地",
    "逗比一般地",
    INVALID_VALUE_STR,
    "大大方方地",
    "简简单单地",
    "兢兢业业地",
    "无法忍受地",
    INVALID_VALUE_STR,
    "毅然地",
    "发春着",
    INVALID_VALUE_STR,
};

string Global::shareText2_en[] = {
    
    " my shoe",
    " my dog",
    " my face",
    INVALID_VALUE_STR,
    " my coat",
    " my underwear",
    " my underwear",
    " my slippers",
    " my socks",
    " my long Johns",
    " my bikini",
    " my bra",
    " my pants",
    INVALID_VALUE_STR,
    " my math teacher",
    " my physics teacher",
    " my political teacher",
    " my chemistry teacher",
    " my Chinese teacher",
    " my English teacher",
    " my PE teacher",
    " my geography teacher",
    " my history teacher",
    " my computer teacher",
    INVALID_VALUE_STR,
    " my left hand",
    " my right hand",
    " my forehead",
    " my stomach",
    " my legs",
    " my toes",
    " my ass",
    " my eye",
    " my little tintin",
    INVALID_VALUE_STR,
    " my predecessor",
    " my boss",
    " my cat",
    " my good friend",
    " my idol",
    " my shit",
    " my knee",
    INVALID_VALUE_STR,
    " my boyfriend",
    " my girlfriend",
    " my dad",
    " my mama",
    " my uncle",
    " my penis",
    INVALID_VALUE_STR,
    " a pond",
    " a big beauty",
    " a spoiled lori",
    " a snappy plane",
    " a sprout of cat",
    INVALID_VALUE_STR,
    " a funny man",
    " a bag of laundry detergent",
    " a fly puppy",
    " a head tree sows",
    " a single dog",
    " a bunch of straight",
    " a lump of shit",
    " a silly roe deer",
    INVALID_VALUE_STR,
    " my deskmate",
    " my front desk",
    " my schoolmate",
    " my colleagues",
    " my little darling",
    INVALID_VALUE_STR,
    " friend's little brother",
    " friend's brother",
    " friend's sister",
    " friend's big aunt",
    " friend's leg",
    " friend's butt",
    " friend's right hand",
    INVALID_VALUE_STR,
    " my bed",
    " my chest",
    " my eggs",
    " my phone",
    INVALID_VALUE_STR,
    " my urinal",
    " my diaper",
    " my sweater",
    " my shorts",
    INVALID_VALUE_STR,
};

string Global::shareText3[] = {
    
    "干掉了",
    "摩擦了",
    "喜欢上了",
    "狂抽了",
    INVALID_VALUE_STR,
    "拔出了",
    "原谅了",
    "含住了",
    "包养了",
    "变成了",
    "扇了",
    "抓起了",
    "鞭挞了",
    "揉捏了",
    "抱住了",
    INVALID_VALUE_STR,
    "捡了",
    "承包了",
    "脱了",
    "搬走",
    "吃了",
    "亮瞎了",
    "偷亲了",
    "败给了",
    "咬住了",
    INVALID_VALUE_STR,
    "踩了",
    "舔了",
    "打了",
    "玩了",
    "偷了",
    "烧死了",
    "套上了",
    "穿上了",
    "顶住了",
    INVALID_VALUE_STR,
    "嘲笑了",
    "刷了",
    "吐了",
    "爱上了",
    "踹了",
    "拿出了",
    "烧了",
    "砍掉了",
    INVALID_VALUE_STR,
    "抚摸了",
    "洗了",
    "摸出了",
    "问候了",
    "怜惜了",
    "钓了",
    "撞死了",
    INVALID_VALUE_STR,
    "嫌弃了",
    "放出了",
    "扔了",
    "拉出了",
    "毁灭了",
    "绑架了",
    "撕掉了",
    INVALID_VALUE_STR,
    "结果了",
    "灭掉了",
    "打掉了",
    "吃掉了",
    "喝掉了",
    "爱上了",
    INVALID_VALUE_STR,
    "爆了",
    "说出了",
    "听到了",
    "叫了",
    "买了",
    INVALID_VALUE_STR,
    "卖了",
    "批发了",
    "网购了",
    "生了",
    "cosplay了",
    INVALID_VALUE_STR,
    "偷摸了",
    "插入了",
    "想起了",
    "爬上了",
    INVALID_VALUE_STR,
    "幻想了",
    "拒绝了",
    INVALID_VALUE_STR,
};

string Global::shareText3_en[] =
{
    " with Aceily",
    " with Adam",
    " with Alcatraz",
    " with Anna",
    " with Anne",
    INVALID_VALUE_STR,
    " with Superman",
    " with Gates",
    " with Clinton",
    " wtth Cyclops",
    " with Black Widow",
    " with lron Man",
    " with The Flash",
    " with The Thing",
    " with Colossus",
    " with Savage Dragon",
    INVALID_VALUE_STR,
    " with Spider Man",
    " with Green Arrow",
    " with Hawkeye",
    " with Doctor Fate",
    " with Batman",
    " with Hulk",
    " with Ms.Marvel",
    " with Celestial Archer",
    " with Captain America",
    " with Mickey Mouse",
    " with Donald Duck",
    " with Buzz Lightyear",
    INVALID_VALUE_STR,
    " with Sheriff Woody",
    " with Homer Simpson",
    " with Marge Simpson",
    " with Bart Simpson",
    " with Tom",
    " with Jerry",
    " with Lady GaGa",
    " with Justin Bieber",
    " with Katy Perry",
    INVALID_VALUE_STR,
    " with Shakira",
    " with Kim Kardashian",
    " with Britney Spears",
    " with Rihanna",
    " with Obama",
    " with Taylor Swift",
    INVALID_VALUE_STR,
    " with Selena Gomez",
    " with Mace Windu",
    " with Obi-Wan Kenobi",
    " with Luke Skywalker",
    " with Anakin",
    " with Avatar",
    INVALID_VALUE_STR,
    " with Baymax",
    " with Cooper",
    " with Optimus Prime",
    " with Decepticon",
    " with Autobot",
    INVALID_VALUE_STR,
    " with Starscream",
    " with Cybertron",
    " with Harry James Potter",
    " with Ron Weasley",
    " with Hermione Granger",
    INVALID_VALUE_STR,
    " with Lord Voldemort",
    " with Dumbledore",
    " with Gandalf",
    " with Aragorn",
    " with Théoden",
    INVALID_VALUE_STR,
    " with Sam",
    " with Baggins",
    " with Pippin",
    " with Merry",
    " with Denethor",
    INVALID_VALUE_STR,
    " with Gollum",
    " with Saruman",
    " with Sauron",
    " with Boromir",
    " with Faramir",
    INVALID_VALUE_STR,
    " with Legolas Greenleaf",
    " with Arwen",
    " with Galadriel",
    " with Elrond",
    " with Gimli",
    " with Glóin",
    " with Treebeard",
    INVALID_VALUE_STR,
};

string Global::shareText4[] = {
    
    "我的滑板鞋~时尚时尚最时尚~",
    "我的洗发水~特技特技加特技~",
    "我的宇宙无敌大帅脸",
    INVALID_VALUE_STR,
    "我的外套",
    "我的内衣",
    "我的内裤",
    "我的拖鞋",
    "我的袜子",
    "我的秋裤",
    "我的头套",
    "我的比基尼",
    "我的胸罩",
    "我的裤子",
    "我的滑板鞋",
    "我的加了特技的洗发水",
    INVALID_VALUE_STR,
    "我的数学老师",
    "我的物理老师",
    "我的政治老师",
    "我的化学老师",
    "我的语文老师",
    "我的英语老师",
    "我的体育老师",
    "我的地理老师",
    "我的历史老师",
    "我的计算机老师",
    "我的高数老师",
    "我的逗比老师",
    INVALID_VALUE_STR,
    "我的左手",
    "我的右手",
    "我的额头",
    "我的肚子",
    "我的腿毛",
    "我的大腿",
    "我的脚趾头",
    "我的屁股",
    "我的狗眼",
    "我的小丁丁",
    "我的大便",
    "我的膝盖",
    INVALID_VALUE_STR,
    "我的前任",
    "我的老板",
    "我的暗恋对象",
    "隔壁熊孩子",
    "隔壁老王",
    "我的班主任",
    "我的好朋友",
    "我的偶像",
    INVALID_VALUE_STR,
    "基友给的100块",
    "撸友给的皮肤",
    "刀友给的人头",
    "朋友给的爱抚",
    "男友给的咸鸭蛋",
    "女友给的臭豆腐",
    "老爸给的火箭筒",
    "老妈给的传送机",
    INVALID_VALUE_STR,
    "一个老大的池塘",
    "一名基情的大汉",
    "一个壮硕的美女",
    "一个娘炮的腹黑",
    "一个抖S的御姐",
    "一个傲娇的萝莉",
    "一次爽快的飞机",
    "一只萌萌的小猫",
    INVALID_VALUE_STR,
    "一坨大便",
    "一个逗比",
    "一包洗衣粉",
    "一只飞翔的小狗",
    "一头上树的母猪",
    "一个单身狗",
    "一堆异性恋",
    "一坨狗屎",
    "一只傻狍子",
    "一个同性恋",
    INVALID_VALUE_STR,
    "我的上铺",
    "我的下铺",
    "我的同桌",
    "我的前桌",
    "我的后桌",
    "我的同学",
    "我的同事",
    "我的暗恋对象",
    "我的小心肝",
    INVALID_VALUE_STR,
    "朋友的小弟弟",
    "朋友的亲哥哥",
    "朋友的姐姐",
    "朋友的妹妹",
    "朋友的大姨妈",
    "朋友的大腿",
    "朋友的屁股",
    "朋友的右手",
    INVALID_VALUE_STR,
    "作者的额头",
    "作者的亲吻",
    "作者的杰伦(就这么不要脸!)",
    "作者的抚摸",
    "作者的爱护",
    "作者的疼爱",
    INVALID_VALUE_STR,
    "作者的错愕",
    "作者的怜惜",
    "作者的钱包",
    "作者的内裤",
    "作者的面具",
    "一个不知道谁能玩出来的彩蛋~么么哒~",
    INVALID_VALUE_STR,
};

string Global::shareText4_en[] = {
    
    
    " in the sea",
    " in the air",
    " in New York",
    INVALID_VALUE_STR,
    " at my sister’s",
    " at my doctor’s",
    " at my hotel",
    " in my bedroom",
    " on my sofa",
    " on my stool",
    " on my desk",
    " in my cupboard",
    " in my office",
    " in my elevator",
    " in my dining room",
    " in my bathhouse",
    " on my bed",
    " in my dormitory",
    INVALID_VALUE_STR,
    " in Canberra",
    " in Mexico",
    " in Berlin",
    " in Paris",
    " in Barcelona",
    " in Tokyo",
    " in London",
    " in Moscow",
    " in the Sahara",
    INVALID_VALUE_STR,
    " in the park",
    " in the desert",
    " in the square",
    " in the street",
    " in the market",
    " in the mall",
    " in the football field",
    " on the basketball court",
    " in the ballpark",
    " in the tennis court",
    INVALID_VALUE_STR,
    " in the moon",
    " in Mars",
    " in Mercury",
    " in Venus",
    " in Jupiter",
    " in Neptune",
    " in Pandora",
    " in Uranus",
    INVALID_VALUE_STR,
    " in Japan",
    " in the U.S",
    " in the UK",
    " in Germany",
    " in France",
    " in Italy",
    " in Australia",
    " in China",
    " in Korea",
    " in Mexico",
    " in Spain",
    " in Portugal",
    " in Russia",
    INVALID_VALUE_STR,
    " under the bed",
    " on the roof",
    " in the bath",
    " in the closet",
    " in the doghouse",
    " under the table",
    " under the statue of liberty",
    " on the bridge",
    INVALID_VALUE_STR,
    " in the pyramid",
    " on the Great Wall",
    " in the Colosseum in Rome",
    " on the Eiffel Tower",
    " in the White House",
    " under the Leaning Tower of Pisa",
    " in cologne cathedral",
    " in the acropolis",
    " in the taj mahal",
    INVALID_VALUE_STR,
    " at my aunt's",
    " at my grandfather's",
    " at my grandma's",
    " at my friend's",
    " at my girlfriend's",
    " at my boyfriend's",
    " at my father's",
    " at my boss's",
    INVALID_VALUE_STR,
    " in the concert",
    " in the exhibition hall",
    " at the fair",
    " on the pitch",
    " in the music conference",
    " in the hall",
    INVALID_VALUE_STR,
    " in my hand",
    " in my ass",
    " in my lap",
    " at my feet",
    " in my stomach",
    " in my body",
    INVALID_VALUE_STR,
    " on my way home",
    " on my way to school",
    " on my way to eat",
    " on the way to work",
    " in the way of travel",
    " on the way to play",
    INVALID_VALUE_STR,
};

Global::Global()
{
    _colorType = colorType_green;
    currentID = 0;
    score = 0;
    highScore = "0";
    isHomeAdSwitch = false;
    isContinue = false;
    lumpMap.clear();
    channel = gInterface->callPlatformFunction(INTERFACE_CALL_FUNCNAME_GetChannel, "");
    
    if (Application::getInstance()->getCurrentLanguage() == LanguageType::CHINESE) {
        isChinese = true;
    }else{
        isChinese = false;
    }
}

Global::~Global()
{
    
}

Global* Global::getInstance()
{
    
    if (!_instance) {
        _instance = new Global();
    }
    
    return _instance;
}

void Global::saveScreenshot(Node* node,const std::string& fileName,const std::function<void(const std::string&)>& callback)

{
    
    Image::Format format;
    
    //进行后缀判断
    
    if(std::string::npos != fileName.find_last_of(".")){
        
        auto extension = fileName.substr(fileName.find_last_of("."),fileName.length());
        
        if (!extension.compare(".png")) {
            
            format = Image::Format::PNG;
            
        } else if(!extension.compare(".jpg")) {
            
            format = Image::Format::JPG;
            
        } else{
            
            CCLOG("cocos2d: the image can only be saved as JPG or PNG format");
            
            return;
            
        }
        
    } else {
        
        CCLOG("cocos2d: the image can only be saved as JPG or PNG format");
        
        return ;
        
    }
    
    //获取屏幕尺寸，初始化一个空的渲染纹理对象
    
    auto renderTexture = RenderTexture::create(gWinSize.width, gWinSize.height, Texture2D::PixelFormat::RGBA8888);
    
    //清空并开始获取
    
    renderTexture->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
    
    //遍历场景节点对象，填充纹理到RenderTexture中
    
    node->visit();
    
    //结束获取
    
    renderTexture->end();
    
    //保存文件
    
    renderTexture->saveToFile(fileName , format);
    
    //使用schedule在下一帧中调用callback函数
    
    auto fullPath = FileUtils::getInstance()->getWritablePath() + fileName;
    
    if (callback != NULL) {
        
        auto scheduleCallback = [&,fullPath,callback](float dt){
            
            callback(fullPath);
            
        };
        
        auto _schedule = node->getScheduler();
        
        _schedule->schedule(scheduleCallback, this, 0.0f,0,0.0f, false, "screenshot");
    }
    
    
}

string Global::getJsonStr(JsonPair* jsonPair, ...)
{
    Json::Value root;
    
    va_list args;
    va_start(args, jsonPair);
    
    if (jsonPair)
    {
        root[jsonPair->getKey()] = jsonPair->getValue();
        JsonPair *i = va_arg(args, JsonPair*);
        while (i)
        {
            root[i->getKey()] = i->getValue();
            i = va_arg(args, JsonPair*);
        }
    }
    
    va_end(args);
    
    string sRet = root.toStyledString();
    sRet = trim(sRet);
    
    return sRet;
}

std::string Global::trim(std::string str, std::string::size_type pos/* = 0*/)
{
    std::string delim = "\n\r\t";
    pos = str.find_first_of(delim, pos);
    if (pos == std::string::npos)
        return str;
    return trim(str.erase(pos, 1));
}

string Global::getSecretText()
{
    string shareText;
    if (isChinese) {
        shareText = "今天";
    }else{
        shareText = "Today,";
    }
    for (int row = 0; row < MapMaxLength; row ++) {
        for (int col = 0; col < MapMaxLength ; col ++) {
            
            int id = 0 ;
            if (gGameMap->getDataLevel(row, col) == 0) {
                
                int max = (int)textMap[col].find(gGameMap->getDataLevel(row, col))->second.size() - 1;
                
                id =  random(0, max);
                
            }else{
                
                id = gGameMap->getDataId(row, col) % (textMap[col].find(gGameMap->getDataLevel(row, col))->second.size() - 1);
                
            }
            shareText.append(textMap[col].find(gGameMap->getDataLevel(row, col))->second.at(id));
            
        }
        
        switch (row) {
            case 0:
                if (isChinese) {
                    shareText.append(",然后");
                }else{
                    shareText.append(".And then ");
                }
                break;
            case 1:
                if (isChinese) {
                    shareText.append(",之后");
                }else{
                    shareText.append(".Then ");
                }
                break;
            case 2:
                if (isChinese) {
                    shareText.append(",最后");
                }else{
                    shareText.append(".At last ");
                }
                break;
            case 3:
                
                break;
        }
        
    }
    if (isChinese) {
        
        shareText.append("。真是有意义的一天啊!");
    }else{
        shareText.append(".Today is a amazing day!");
    }
    
    return shareText;
}

void Global::loadTextMap()
{
    if (isChinese) {
        
        loadMap(shareText1, sizeof(shareText1) / sizeof(shareText1[0]), 0);
        loadMap(shareText2, sizeof(shareText2) / sizeof(shareText2[0]), 1);
        loadMap(shareText3, sizeof(shareText3) / sizeof(shareText3[0]), 2);
        loadMap(shareText4, sizeof(shareText4) / sizeof(shareText4[0]), 3);
    }else{
        
        loadMap(shareText1_en, sizeof(shareText1_en) / sizeof(shareText1_en[0]), 0);
        loadMap(shareText2_en, sizeof(shareText2_en) / sizeof(shareText2_en[0]), 1);
        loadMap(shareText3_en, sizeof(shareText3_en) / sizeof(shareText3_en[0]), 2);
        loadMap(shareText4_en, sizeof(shareText4_en) / sizeof(shareText4_en[0]), 3);
    }
}

void Global::loadMap(string *str, int size, int count)
{
    //    int aryNum = sizeof(str) / sizeof(str[0]);
    int aryNum = size;
    
    int level = -1;
    vector< string > tmpVec;
    
    for (int i = 0; i < aryNum; i ++)
    {
        if (str[i] == INVALID_VALUE_STR) //表尾
        {
            level ++;
            CCAssert(level != -1 && tmpVec.size() != 0, "");
            textMap[count].insert( make_pair(level, tmpVec) );
            tmpVec.clear();
        }
        else //表数据
        {
            // 读取表
            tmpVec.push_back( str[i] );
            
        }
    }
}


Rect Global::getNodeRect(Node* node)
{
    
    assert(node != nullptr);
    Rect rect ;
    
    Vec2 ap = node->getAnchorPoint();
    float x = node->getPositionX() - (node->getContentSize().width) * ap.x;
    float y = node->getPositionY() - (node->getContentSize().height) * ap.y;
    float width = node->getContentSize().width;
    float height = node->getContentSize().height;
    rect = Rect(x, y, width, height);
    
    return rect;
}

string Global::getDateNow(){
    
    struct timeval nowTimeval;
    gettimeofday(&nowTimeval, NULL);
    struct tm * tm;
    time_t time_sec ;
    time_sec = nowTimeval.tv_sec;
    tm = localtime(&time_sec);
    int m_year = tm->tm_year;
    int m_mon = tm->tm_mon;
    int m_mday = tm->tm_mday;
    int m_wek = tm->tm_wday;
    
    string yearStr = toString(1900 + m_year);
    
    string monStr;
    switch (m_mon) {
        case 0:
            monStr = "Jan.";
            break;
        case 1:
            monStr = "Feb.";
            break;
        case 2:
            monStr = "Mar.";
            break;
        case 3:
            monStr = "Apr.";
            break;
        case 4:
            monStr = "May.";
            break;
        case 5:
            monStr = "Jun.";
            break;
        case 6:
            monStr = "Jul.";
            break;
        case 7:
            monStr = "Aug.";
            break;
        case 8:
            monStr = "Sept.";
            break;
        case 9:
            monStr = "Oct.";
            break;
        case 10:
            monStr = "Nov.";
            break;
        case 11:
            monStr = "Dec.";
            break;
    }
    
    string mdayStr;
    switch (m_mday % 10) {
        case 1:
            mdayStr = toString(m_mday)+"st";
            break;
            
        case 2:
            mdayStr = toString(m_mday)+"nd";
            break;
            
        default:
            mdayStr = toString(m_mday)+"th";
            break;
    }

    
    
    
    string wekStr;
    switch (m_wek) {
        case 0:
            wekStr = "Sunday";
            break;
        case 1:
            wekStr = "Monday";
            break;
        case 2:
            wekStr = "Tuesday";
            break;
        case 3:
            wekStr = "Wednesday";
            break;
        case 4:
            wekStr = "Thursday";
            break;
        case 5:
            wekStr = "Friday";
            break;
        case 6:
            wekStr = "Saturday";
            break;
    }
    
    
    string weatherStr = "Sunny";
    
    string dateStr = wekStr + " " + monStr + mdayStr + " " + yearStr + "     " + weatherStr;
    CCLOG("%s",dateStr.c_str());
    return dateStr;
}

