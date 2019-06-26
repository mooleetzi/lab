let response=$.ajax({url:'http://www.cdutzy.com/API/allNews',async:false}).responseJSON;
let img=response.results;
let slide = document.getElementsByClassName('slide-container')[0];
for (let i = 0; i <img.length; i++) {
    let now = document.createElement('div');
    now.className = 'slide-item';
    now.innerHTML = '<img width="100%" height="auto" src='+img[i].passage_img+'>';
    if (i == 0)
        now.className+=' show';
    else
        now.className+=' not-show';
    slide.appendChild(now);
}
let showIndex = 0, timeId = null;
let slide_item = document.getElementsByClassName('slide-item');

function play() {
    slide_item[showIndex ].className = 'slide-item not-show';
    showIndex = (showIndex + 1) % img.length;
    slide_item[showIndex].className = 'slide-item show';
}

function autoPlay() {
    timeId = setInterval(play, 2000);
}
autoPlay();