let slide = document.getElementsByClassName('slide-container')[0];
for (let i = 1; i <= 5; i++) {
    let now = document.createElement('div');
    now.className = 'slide-item';
    now.innerHTML = '<img src="static/img/' + i + '.jpg">';
    if (i == 1)
        now.className+=' show';
    else
        now.className+=' not-show';
    slide.appendChild(now);
}
let showIndex = 0, timeId = null;
let slide_item = document.getElementsByClassName('slide-item');

function play() {
    // console.log(showIndex,slide_item);
    slide_item[showIndex ].className = 'slide-item not-show';
    showIndex = (showIndex + 1) % 5;
    slide_item[showIndex].className = 'slide-item show';
}

function autoPlay() {
    timeId = setInterval(play, 2000);
}

autoPlay();