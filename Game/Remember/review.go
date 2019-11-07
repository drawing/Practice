package main

import (
	"flag"
	"log"
	"math/rand"
	"time"

	"github.com/gizak/termui"
	"github.com/nsf/termbox-go"
)

var codes = map[string]string{
	"0":  "鸡蛋",
	"1":  "树",
	"2":  "鹅",
	"3":  "弹簧",
	"4":  "帆船",
	"5":  "鱼钩",
	"6":  "哨子",
	"7":  "镰刀",
	"8":  "葫芦",
	"9":  "淋浴头",
	"00": "眼镜",
	"01": "人妖",
	"02": "铃儿",
	"03": "灵山大佛",
	"04": "零食",
	"05": "领舞",
	"06": "左轮手枪",
	"07": "灵气(云)",
	"08": "篱笆",
	"09": "灵鹫(老鹰)",
	"10": "棒球",
	"11": "筷子",
	"12": "椅儿",
	"13": "医生",
	"14": "钥匙",
	"15": "鹦鹉",
	"16": "石榴",
	"17": "仪器",
	"18": "腰包",
	"19": "药酒",
	"20": "香烟",
	"21": "鳄鱼",
	"22": "双胞胎",
	"23": "和尚",
	"24": "时钟(意义)",
	"25": "二胡",
	"26": "河流",
	"27": "耳机",
	"28": "恶霸",
	"29": "鹅脚",
	"30": "三菱镜",
	"31": "山药",
	"32": "扇儿",
	"33": "闪闪金砖",
	"34": "三点式",
	"35": "山虎",
	"36": "山鹿",
	"37": "山鸡",
	"38": "妇女",
	"39": "999感冒灵",
	"40": "司令",
	"41": "死鱼",
	"42": "柿儿",
	"43": "石山",
	"44": "蛇(咝咝)",
	"45": "师傅",
	"46": "饲料",
	"47": "司机",
	"48": "石板",
	"49": "湿狗",
	"50": "五环",
	"51": "工人",
	"52": "鼓儿",
	"53": "火山",
	"54": "巫师",
	"55": "(火车)呜呜",
	"56": "蜗牛",
	"57": "武器",
	"58": "尾巴",
	"59": "蜈蚣",
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
	"75": "西服",
	"76": "汽油",
	"77": "玫瑰(七夕)",
	"78": "西瓜",
	"79": "气球",
	"80": "巴黎铁塔",
	"81": "白蚁",
	"82": "靶儿",
	"83": "花生",
	"84": "扳手",
	"85": "宝物",
	"86": "八路",
	"87": "白棋",
	"88": "人民币",
	"89": "芭蕉",
	"90": "精灵",
	"91": "球衣",
	"92": "球儿",
	"93": "救生圈",
	"94": "首饰",
	"95": "旧屋",
	"96": "酒炉",
	"97": "酒旗",
	"98": "球拍",
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

	tips := termui.NewPar(":PRESS q TO QUIT Practice")
	tips.Height = 3
	tips.Width = screenWidth
	tips.TextFgColor = termui.ColorWhite
	tips.BorderLabel = "TIPS"
	tips.BorderFg = termui.ColorCyan

	prograss := termui.NewGauge()
	prograss.Percent = 0
	prograss.Width = screenWidth
	prograss.Height = 3
	prograss.Y = screenHeight - 3
	prograss.BorderLabel = "Prograss"
	prograss.BarColor = termui.ColorGreen
	prograss.BorderFg = termui.ColorWhite
	prograss.BorderLabelFg = termui.ColorCyan

	const rowSize = 25
	rowsQuestion := make([][]string, rowSize)

	rowsQuestion[0] = []string{"    Question    ", "    Answer    "}

	tableQuestion := termui.NewTable()
	tableQuestion.Rows = rowsQuestion
	tableQuestion.FgColor = termui.ColorWhite
	tableQuestion.BgColor = termui.ColorDefault
	tableQuestion.Y = 4
	tableQuestion.X = 0
	tableQuestion.Separator = false
	tableQuestion.Width = screenWidth
	tableQuestion.Height = rowSize + 2
	if tableQuestion.Separator {
		tableQuestion.Height = 2*rowSize + 1
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

	termui.Handle("/sys/kbd/q", func(termui.Event) {
		termui.StopLoop()
	})
	termui.Handle("/sys/kbd/<escape>", func(termui.Event) {
		termui.StopLoop()
	})
	termui.Handle("/sys/kbd/<enter>", func(termui.Event) {
		step <- 1
	})

	termui.Loop()
}
