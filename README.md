# Tak tok

Experiment on GBA development.

## Notes

For video mode 4, two things:
- Do not use transparency in an image.
- Apparently 16x16 ratio will lead to trouble. Other ratios as 70x90 and 90x90 do work.

## GBADEV Discord thread on timing

-- me

Hello there! I am new to GBA programming and currently I am learning more about timers. I use [this](https://www.coranac.com/tonc/text/timers.htm) tutorial.
Last section about the tutorial says that 

> Of course, I could have just as easily used the VBlank to keep track of the seconds, which is how it's usually done anyway.

but unfortunately I could not find any tutorial to help me out on timers using VBlank. Do any of guys have a suggestion on where to learn how to use timers with VBlank? Many thanks in advance!

-- GValiente

I think he means that in each minute there's 59.97 vblank interrupts
so if you wait for vblank with an interrupt, you can use that to measure time

-- Lysander / lambda

each second*
and yeah, roughly speaking
you could do something akin to this
```c
int frames = 0;
int seconds = 0;

while (1)
{
    VBlankIntrWait();
    frames += 1;
    
    // Could also do seconds = frames / 60, but that requires slow integer division
    if (frames == 60)
    {
        frames = 0;
        seconds += 1;
    }
}
```

-- Gericom

Dividing by 60 in arm mode is fast btw, because it will become a long mul

-- me

I'm too noob to know what arm mode is yet, I'll stick to @Lysander / lambda example for now 😛

-- Lysander / lambda

(in essence, the CPU supports two different instruction sets, a more complex one called arm and a condensed one called thumb. thumb is generally preferred due to certain limitations of the hardware, but it lacks the ability to optimize certain operations, like integer division by a constant. my code is simple enough to run fast no matter what mode you use)

## Useful links
https://www.reinterpretcast.com/writing-a-game-boy-advance-game
https://devkitpro.org/wiki/devkitPro_pacman
https://github.com/JamieDStewart/GBA_Tutorials/tree/master/002_Hello_Input
https://gbadev.net/
https://git.brainbaking.com/wgroeneveld/gba-bitmap-engine/
http://www.coranac.com/tonc/text/toc.htm
https://jamiedstewart.github.io/gba%20dev/2019/03/21/GBA-Dev-Input-Handling.html
https://gvaliente.github.io/butano/faq.html#faq_transparent_color
