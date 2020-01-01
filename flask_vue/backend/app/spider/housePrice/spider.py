#!/usr/bin/env python3
# -*- coding: utf-8 -*-

' a house price spider '

__author__ = 'MK'

import requests
from bs4 import BeautifulSoup

class House:
    def __init__(self):
        self.target = 'https://cd.fang.lianjia.com/loupan/jinjiang-qingyang' \
                      '-wuhou-gaoxin7-chenghua-jinniu-tianfuxinqu-gaoxinxi1' \
                      '-shuangliu-wenjiang-pidou-longquanyi-xindou-' \
                      'qingbaijiang/bp0ep300pg'
        self.HEADERS = {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) '
                          'AppleWebKit/537.36 (KHTML, like Gecko) '
                          'Chrome/65.0.3325.181 Safari/537.36'
        }
        self.urls = []

    def get_urls(self):
        for i in range(1, 86):
            url = self.target + str(i)
            self.urls.append(url)

    def get_context(self, url):
        res = requests.get(url=url, headers=self.HEADERS)
        res.encoding = 'utf-8'
        html = res.text
        div_bf = BeautifulSoup(html, 'html5lib')
        names = div_bf.find_all('a', class_='name')

        locations = div_bf.find_all('div', class_='resblock-location')
        qus = BeautifulSoup(str(locations), 'html5lib').find_all('span')
        qus = qus[::2]

        main_prices = div_bf.find_all('div', class_='main-price')
        prices = BeautifulSoup(str(main_prices), 'html5lib'). \
            find_all('span', class_='number')

        result = ''
        for i in range(len(names)):
            if prices[i].string == '价格待定' or \
                    int(float(prices[i].string)) < 3000:
                continue
            result = result + names[i].string + ' '
            result = result + qus[i].string + ' '
            result = result + prices[i].string + '\n'

        return result

    def writer(self, path, text):
        with open(path, 'a', encoding='utf-8') as f_ob:
            f_ob.write(text)

    def do_it(self, path):
        self.get_urls()
        with open(path, 'w', encoding='utf-8'):
            pass

        for url in self.urls:
            self.writer(path, self.get_context(url))
        # for i in range(85):
        #     self.writer(path, self.get_context(self.urls[i]))
        #     sys.stdout.write('\rdownload:{}%'
        #                      .format(i+1))
        #     sys.stdout.flush()

    def get_avg(self, li):
        sum = 0
        for item in li:
            sum += item
        return sum / len(li)

    def sum_it(self, path, save_path):
        # {city: '锦江',      0
        # {city: '青羊',      1
        # {city: '武侯',      2
        # {city: '高新',      3
        # {city: '成华',      4
        # {city: '金牛',      5
        # {city: '天府新区',  6
        # {city: '高新西',    7
        # {city: '双流',      8
        # {city: '温江',      9
        # {city: '郫都',      10
        # {city: '龙泉驿',     11
        # {city: '新都',       12
        # {city: '青白江',     13
        data = [[], [], [], [], [], [], [], [], [], [], [], [], [], []]
        sum = [[], [], [], [], [], [], [], [], [], [], [], [], [], []]
        with open(path, 'r', encoding='utf-8') as f_ob:
            for line in f_ob:
                message = line.split()
                if message[1] == '锦江':
                    i = 0
                elif message[1] == '青羊':
                    i = 1
                elif message[1] == '武侯':
                    i = 2
                elif message[1] == '高新':
                    i = 3
                elif message[1] == '成华':
                    i = 4
                elif message[1] == '金牛':
                    i = 5
                elif message[1] == '天府新区':
                    i = 6
                elif message[1] == '高新西':
                    i = 7
                elif message[1] == '双流':
                    i = 8
                elif message[1] == '温江':
                    i = 9
                elif message[1] == '郫都':
                    i = 10
                elif message[1] == '龙泉驿':
                    i = 11
                elif message[1] == '新都':
                    i = 12
                elif message[1] == '青白江':
                    i = 13
                data[i].append(int(message[2]))
            for i in range(len(data)):
                sum[i].append(min(data[i]))
                sum[i].append(max(data[i]))
                sum[i].append(int(self.get_avg(data[i])))

        with open(save_path, 'w', encoding='utf-8') as f:
            for item in sum:
                f.write('{} {} {}\n' .format(item[0], item[1], item[2]))

    @classmethod
    def get_data(cls):
        sum = []
        with open('sum.txt') as f_ob:
            for line in f_ob:
                data = line.split()
                sum.append([int(data[0]), int(data[1]), int(data[2])])
        # 返回的sum是一个二维数组：
        #     sum = [
        #         [最低, 最高, 平均],
        #         [最低, 最高, 平均],
        #         ........
        #     ]
        return sum

    @staticmethod
    def get_option():
        asb=House.get_data()
        option ={
            'legend': {},
            'tooltip': {},
            'dataset': {
                'dimensions': ['city', '最低', '最高', '平均'],
                'source': [
                    {'city': '锦江', '最低': asb[0][0], '最高': asb[0][1], '平均': asb[0][2]},
                    {'city': '青羊', '最低': asb[1][0], '最高': asb[1][1], '平均': asb[1][2]},
                    {'city': '武侯', '最低': asb[2][0], '最高': asb[2][1], '平均': asb[2][2]},
                    {'city': '高新', '最低': asb[3][0], '最高': asb[3][1], '平均': asb[3][2]},
                    {'city': '成华', '最低': asb[4][0], '最高': asb[4][1], '平均': asb[4][2]},
                    {'city': '金牛', '最低': asb[5][0], '最高': asb[5][1], '平均': asb[5][2]},
                    {'city': '天府新区', '最低': asb[6][0], '最高': asb[6][1], '平均': asb[6][2]},
                    {'city': '高新西', '最低': asb[7][0], '最高': asb[7][1], '平均': asb[7][2]},
                    {'city': '双流', '最低': asb[8][0], '最高': asb[8][1], '平均': asb[8][2]},
                    {'city': '温江', '最低': asb[9][0], '最高': asb[9][1], '平均': asb[9][2]},
                    {'city': '郫都', '最低': asb[10][0], '最高': asb[10][1], '平均': asb[10][2]},
                    {'city': '龙泉驿', '最低': asb[11][0], '最高': asb[11][1], '平均': asb[11][2]},
                    {'city': '新都', '最低': asb[12][0], '最高': asb[12][1], '平均': asb[12][2]},
                    {'city': '青白江', '最低': asb[13][0], '最高': asb[13][1], '平均': asb[13][2]},
                ]
            },
            'xAxis': {'type': 'category',
                      'axisLabel': {
                          'interval': 0,
                          'rotate': "0",
                          'textStyle': {
                              'fontSize': 20,
                          },
                      }
                      },
            'yAxis': {},

            'series': [
                {'type' : 'bar'},
                {'type': 'bar'},
                {'type': 'bar'}
            ]
        };
        return option

# house = House()
# house.do_it('house.txt')
# house.sum_it('house.txt', 'sum.txt')
