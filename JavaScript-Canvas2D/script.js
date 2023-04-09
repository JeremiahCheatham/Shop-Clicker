"use strict";

const canvas = document.getElementById('gameCanvas');
const canvasRect = canvas.getBoundingClientRect();
const ctx = canvas.getContext('2d');

// Set the font properties
ctx.font = '35px FreeSansBold';
ctx.fillStyle = 'white';
ctx.textBaseline = "top";

ctx.imageSmoothingEnabled = false;
ctx.imageRendering = "pixelated";

let playing = false
let time = 0
let money = 0
let level = 1
let clicks = 0
let interval = 1

const backgroundsky = new Image();
const backgroundhills = new Image();
const background = new Image();
const splash = new Image();

const level1 = new Image();
const level2 = new Image();
const level3 = new Image();
const level4 = new Image();
const level5 = new Image();
const level6 = new Image();

const upgrade1 = new Image();
const upgrade2 = new Image();
const upgrade3 = new Image();
const upgrade4 = new Image();
const upgrade5 = new Image();

const music = new Audio();
const musix = new Audio();

// All assets to be loaded.
const resources = [
    { src: 'images/background.png', img: backgroundsky },
    { src: 'images/terrain.png', img: backgroundhills },
    { src: 'images/ground.png', img: background },
    { src: 'images/splashscreen.png', img: splash },
    { src: 'images/level1.png', img: level1 },
    { src: 'images/level2.png', img: level2 },
    { src: 'images/level3.png', img: level3 },
    { src: 'images/level4.png', img: level4 },
    { src: 'images/level5.png', img: level5 },
    { src: 'images/level6.png', img: level6 },
    { src: 'images/upgrade-sign1.png', img: upgrade1 },
    { src: 'images/upgrade-sign2.png', img: upgrade2 },
    { src: 'images/upgrade-sign3.png', img: upgrade3 },
    { src: 'images/upgrade-sign4.png', img: upgrade4 },
    { src: 'images/upgrade-sign5.png', img: upgrade5 },
    { src: 'music/rumble.mp3', audio: music, loop: true },
    { src: 'music/jazz.ogg', audio: musix, loop: true },
    { src: 'fonts/freesansbold.ttf', font: 'FreeSansBold' }
];

const promises = resources.map(({ src, img, audio, font, loop }) => {
    return new Promise((resolve) => {
        if (img) {
            img.src = src;
            img.addEventListener('load', resolve);
        } else if (audio) {
            audio.src = src;
            audio.loop = loop || false;
            audio.addEventListener('canplaythrough', resolve);
        } else if (font) {
            const fontFace = new FontFace(font, `url(${src})`);
            fontFace.load().then(() => {
                document.fonts.add(fontFace);
                resolve();
            });
        } else {
            resolve();
        }
    });
});
  
const resourcesLoadedPromise = Promise.all(promises);

resourcesLoadedPromise.then(() => {

    if (Math.floor(Math.random() * 2) == 0) {
        music.play();
    } else {
        musix.play();
    }

    function gameLoop(timeStamp) {
        let dt = (timeStamp - lastTime) / 1000;
        lastTime = timeStamp;

        // Update game state
        if (playing) {
            time = time + dt
            if (time >= interval && clicks >= (level * 4)) {
                clicks = clicks - level * 4
                interval = 0.8
                money = money + level
                time = 0
            }
        }

        // Draw the score on the canvas
        ctx.drawImage(backgroundsky, 0, 0, 800, 600);
        ctx.drawImage(backgroundhills, 0, 400, 800, 200);
        ctx.drawImage(background, 0, 500, 800, 100);

        if (playing) {
            ctx.fillText(`Stock: ${clicks}`, 5, 5);
            const text = `Funds: ${money}`;
            const textWidth = ctx.measureText(text).width + 5;
            ctx.fillText(text, canvas.width - textWidth, 5);
            if (level == 1) {
                ctx.drawImage(level1, 150, 220, 500, 400);
                ctx.drawImage(upgrade1, 250, 50, 300, 50);
            } else if (level == 2) {
                ctx.drawImage(level2, 150, 220, 500, 400);
                ctx.drawImage(upgrade2, 250, 50, 300, 50);
            } else if (level == 3) {
                ctx.drawImage(level3, 150, 220, 500, 400);
                ctx.drawImage(upgrade3, 250, 50, 300, 50);
            } else if (level == 4) {
                ctx.drawImage(level4, 150, 220, 500, 400);
                ctx.drawImage(upgrade4, 250, 50, 300, 50);
            } else if (level == 5) {
                ctx.drawImage(level5, 150, 220, 500, 400);
                ctx.drawImage(upgrade5, 250, 50, 300, 50);
            } else if (level == 6) {
                ctx.drawImage(level6, 150, 220, 500, 400);
            }
        } else {
            ctx.drawImage(splash, 2, 2, 800, 600);
        }

        // Schedule the next animation frame
        requestAnimationFrame(gameLoop);
    }

    function reset() {
        time = 0;
        money = 0;
        level = 1;
        clicks = 0;
        interval = 1;
    }
    
    window.addEventListener('keydown', (event) => {
        if (event.key === 'Escape') {
            window.close();
        } else if (event.key === ' ') {
            if (playing) {
                reset()
            } else {
                playing = true;
            }
        }
    });

    window.addEventListener('click', (event) => {
        // Handle button click
        let x = event.clientX - canvasRect.left; // Mouse X position
        let y = event.clientY - canvasRect.top; // Mouse Y position
        let button = event.button; // Mouse button (0 for left, 1 for middle, 2 for right)
        if (playing) {
            if (button == 0) {
                if (y > 220 && y < 600) {
                    if (x > 150 && x < 650) {
                        clicks = clicks + level
                    }
                } else if (y > 50 && y < 100) {
                    if (x > 250 && x < 550) {
                        if (level == 1) {
                            if (money >= 70) {
                                level += 1
                                money -= 70
                            }
                        } else if (level == 2) {
                            if (money >= 140) {
                                level += 1
                                money -= 140
                            }
                        } else if (level == 3) {
                            if (money >= 210) {
                                level += 1
                                money -= 210
                            }
                        } else if (level == 4) {
                            if (money >= 280) {
                                level += 1
                                money -= 280
                            }
                        } else if (level == 5) {
                            if (money >= 350) {
                                level += 1
                                money -= 350
                            }
                        }

                    }
                }
            }
        }
    });

    let lastTime = performance.now();
  
    // Start the game loop
    requestAnimationFrame(gameLoop);
}).catch((err) => {
    console.error('Error loading resources:', err);
});