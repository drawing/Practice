package main

import (
	"flag"
	"log"
	"math/rand"
	"time"

	termui "github.com/gizak/termui/v3"
	"github.com/gizak/termui/v3/widgets"

	"github.com/nsf/termbox-go"
)

var codes = map[string]string{
	"0":  "鸡蛋",
	"1":  "树",
	"2":  "鹅",
	"3":  "弹簧",
	"4":  "国旗",
	"5":  "鱼钩",
	"6":  "哨子",
	"7":  "镰刀",
	"8":  "葫芦",
	"9":  "淋浴头",
	"00": "眼镜",
	"01": "灵异(神灯)",
	"02": "铃儿",
	"03": "灵山大佛",
	"04": "零食",
	"05": "领舞",
	"06": "左轮手枪",
	"07": "灵气(云雾)",
	"08": "篱笆",
	"09": "灵鹫(老鹰)",
	"10": "棒球",
	"11": "筷子",
	"12": "婴儿",
	"13": "要塞",
	"14": "钥匙",
	"15": "药物",
	"16": "杨柳",
	"17": "妖气(有妖气漫画)",
	"18": "腰包",
	"19": "药酒",
	"20": "香烟",
	"21": "鳄鱼",
	"22": "双胞胎",
	"23": "耳塞",
	"24": "小时(时钟)",
	"25": "二胡",
	"26": "河流",
	"27": "耳机",
	"28": "恶霸",
	"29": "阿胶",
	"30": "三菱镜",
	"31": "山药",
	"32": "扇儿",
	"33": "三三禁手(五子棋)",
	"34": "三点式",
	"35": "珊瑚",
	"36": "山鹿",
	"37": "山鸡",
	"38": "妇女",
	"39": "三角尺",
	"40": "司令",
	"41": "死鱼",
	"42": "柿儿",
	"43": "石山",
	"44": "蛇(咝咝)",
	"45": "师傅",
	"46": "饲料",
	"47": "司机",
	"48": "石板",
	"49": "四九城",
	"50": "五环",
	"51": "劳动(工人)",
	"52": "鼓儿",
	"53": "火山",
	"54": "青年/巫师/武士",
	"55": "(火车)呜呜",
	"56": "蜗牛",
	"57": "武器(手枪)",
	"58": "苦瓜",
	"59": "五角(大楼)",
	"60": "榴莲",
	"61": "儿童",
	"62": "牛儿",
	"63": "流沙",
	"64": "螺丝",
	"65": "尿壶",
	"66": "蝌蚪(形状)",
	"67": "油漆",
	"68": "喇叭",
	"69": "太极图",
	"70": "麒麟",
	"71": "机翼",
	"72": "企鹅",
	"73": "漆伞",
	"74": "骑士",
	"75": "积木",
	"76": "汽油",
	"77": "玫瑰(七夕)",
	"78": "西瓜",
	"79": "气球",
	"80": "巴黎铁塔",
	"81": "白蚁",
	"82": "靶儿",
	"83": "花生",
	"84": "84消毒液",
	"85": "宝物",
	"86": "八路",
	"87": "白棋",
	"88": "人民币",
	"89": "芭蕉",
	"90": "精灵",
	"91": "球衣",
	"92": "球儿",
	"93": "救生圈",
	"94": "教师",
	"95": "旧屋",
	"96": "酒炉",
	"97": "酒旗",
	"98": "球拍/酒吧",
	"99": "舅舅",
}

func randQuestion(data [][]string) {
	for i := 0; i < len(data)-1; i++ {
		left := len(data) - 1 - i
		index := int(rand.Int31())%left + i + 1

		tmp := data[i]
		data[i] = data[index]
		data[index] = tmp
	}
}

var waitTime = flag.Duration("wait", time.Second*3, "wait time every question, default 3s")
var mode = flag.Int("mode", 1, "display mode(1-digit 2-mean 3-both), default 1")

func main() {
	flag.Parse()

	rand.Seed(time.Now().Unix())

	if *mode&0x3 == 0 {
		log.Fatalln("mode must be 1 or 2 or 3")
	}

	err := termui.Init()
	if err != nil {
		log.Fatalln("termui init failed:", err)
	}
	defer termui.Close()

	screenWidth, screenHeight := termbox.Size()

	questions := [][]string{}
	for k, v := range codes {
		if *mode&0x1 != 0 {
			issue1 := []string{k, v}
			questions = append(questions, issue1)
		}

		if *mode&0x2 != 0 {
			issue2 := []string{v, k}
			questions = append(questions, issue2)
		}
	}
	wait := time.NewTimer(time.Second * 60)
	if *waitTime == 0 {
		wait.Stop()
	} else {
		wait.Reset(*waitTime)
	}

	tips := widgets.NewParagraph()
	tips.Text = ":PRESS q TO QUIT Practice"
	tips.SetRect(0, 0, screenWidth, 3)
	tips.TextStyle.Fg = termui.ColorWhite
	tips.BorderStyle.Fg = termui.ColorCyan
	tips.Title = "TIPS"
	tips.TitleStyle.Fg = termui.ColorYellow

	prograss := widgets.NewGauge()
	prograss.Percent = 0
	prograss.SetRect(0, screenHeight - 3, screenWidth, screenHeight)
	prograss.BarColor = termui.ColorGreen
	prograss.Title = "Prograss"
	prograss.BorderStyle.Fg = termui.ColorCyan
	prograss.TitleStyle.Fg = termui.ColorYellow

	const rowSize = 25
	rowsQuestion := make([][]string, rowSize)

	rowsQuestion[0] = []string{"    Question    ", "    Answer    "}

	tableQuestion := widgets.NewTable()
	tableQuestion.Rows = rowsQuestion
	tableQuestion.TextStyle.Fg = termui.ColorWhite
	tableQuestion.SetRect(0, 4, screenWidth, 4 + rowSize + 2)
	tableQuestion.BorderStyle.Fg = termui.ColorCyan
	tableQuestion.RowSeparator = false
	if tableQuestion.RowSeparator {
		tableQuestion.SetRect(0, 4, screenWidth, 4 + 2*rowSize + 1)
	}

	step := make(chan int)
	go func() {
		rows := tableQuestion.Rows
		index := 1
		for {
			randQuestion(questions)

			for offset, issue := range questions {
				row := []string{issue[0], ""}
				rows[index] = row
				prograss.Percent = 100 * offset / len(questions)

				termui.Render(prograss, tableQuestion)

				select {
				case <-step:
					if *waitTime != 0 {
						wait.Reset(*waitTime)
					}
				case <-wait.C:
					wait.Reset(*waitTime)
				}

				row[1] = issue[1]
				rows[index] = row

				if index == rowSize-1 {
					for i := 2; i < rowSize; i++ {
						rows[i-1] = rows[i]
					}
				} else {
					index++
				}
			}
		}
	}()

	termui.Render(tips, prograss, tableQuestion)

	uiEvents := termui.PollEvents()

	for {
		select {
		case e := <-uiEvents:
			switch e.ID {
			case "q", "<C-c>", "<Escape>":
				return
			case "<Enter>", "<Space>":
				step <- 1
			}
		}
	}
}
