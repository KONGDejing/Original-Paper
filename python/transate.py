import urllib.request
import json
import time

while True:
    content = input("请输入内容：(输入q!退出)")
    if content == 'q!':
        break

    #head = {}
    #head['User-Agent']= 'User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.140 Safari/537.36 Edge/17.17134'


    #url = 'http://fanyi.youdao.com/translate_o?smartresult=dict&smartresult=rule'
    url='http://fanyi.youdao.com/translate?smartresult=dict&smartresult=rule '
    data = {}
    data['action']='FY_BY_CLICKBUTTION'
    data['by']='435192ea8debc53c68e5c13d953099ff'
    data['client']='fanyideskweb'
    data['doctype']='json'
    data['type']= 'AUTO'
    data['i'] = content  #'perfection'#'I love FishC.com!'
    data['keyfrom']='fanyi.web'
    data['salt']='15564673978077'
    data['sign']='1b27ebc5e2b9df83b7f16d2881ba05c0'
    data['smartresult']='dict'
    data['to']= 'AUTO'
    data['ts']='1556467397807'
    data['version']='2.1'
    #data['xmlVersion']= '1.6'
    #data['ue']='UTF-8'
    #data['typoResult']='true'

    data= urllib.parse.urlencode(data).encode('utf-8')


    req = urllib.request.Request(url,data)
    req.add_header('User-Agent','User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.140 Safari/537.36 Edge/17.17134')

    response = urllib.request.urlopen(req)
    html = response.read().decode('utf-8')

    target = json.loads(html)
    target = target['translateResult'][0][0]['tgt']

    #print(html)
    print("翻译结果:%s" % target)
    time.sleep(1)
