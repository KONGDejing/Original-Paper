import urllib.request
import urllib.parse
import os

def url_open(url):
    req = urllib.request.Request(url)
    req.add_header('User-Agent','Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.131 Safari/537.36')
    response = urllib.request.urlopen(url)
    html = response.read()
    print(url)
    return html

def get_page(url):
    '''
    req = urllib.request.Request(url)
    req.add_header('User-Agent','Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.131 Safari/537.36')
    response = urllib.request.urlopen(url)
    html = response.read().decode('utf-8')
    '''
    html= url_open(url).decode('utf-8')
    
    a=html.find('current-comment-page')+23
    b=html.find(']',a)

    #print(html)
    return html[a:b]


def find_imgs(url):
    html = url_open(url).decode('utf-8')
    img_addrs=[]

    a= html.find("img src=")
    while a!=-1:  
        b= html.find('.jpg',a,a+255)
        if b!=-1:
            img_addrs.append('http:'+html[a+9:b+4])
        else:
            b=a+9
        a= html.find("img src=",b)
    for each in img_addrs:
        print(each)

    return img_addrs
        

def save_imgs(folder,img_addrs):
    for each in img_addrs:
        filename = each.split('/')[-1]
        with open(filename,'wb') as f:
            img = url_open(each)
            f.write(img)
    

def download_mm(folder='OOXX',pages=10):
    os.mkdir(folder)
    os.chdir(folder)

    url='http://jandan.net/ooxx/'
    page_num = int(get_page(url))
    print(page_num)

    for i in range(pages):
        page_num -= i
        page_url = url + 'page-' + str(page_num) +'#comments'
        image_addrs = find_imgs(page_url)
        save_imgs(folder,image_addrs)

if __name__ == '__main__':
    download_mm()
