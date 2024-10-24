# Breakout

W Kavanagh. June Summer 2024

## controls

A/D to move the paddle right and left.
P to pause.

## Powerups

big/small paddle (blue)
fast/slow ball (fancy yellow)
fire ball (green)

# Tasklist

## Suggested fixes

* Fix the compiler issues in the code

## Suggested tasks

* Improved VFX (ball trail, paddle hit response, brick particle destruction)
* Better UI (progress bar rather than timer for countdown).
* GameLoop
* Better ball physics (Box2D)
* Leaderboards
* More ball types (e.g., multiball, sticky ball [where you shoot the ball from the paddle every time], tiny ball, big ball, brick-tracking ball)
* Sounds with increasing tone between bounces.
* Implement commentary with calls to an LLM such as LLama

# Time Details and Changelist
<Add information to this section about the time you've taken for this task along with a professional changelist.>
Fixed Compile time issues
Added mouse movement
added score counter with UI
added shared brick textures

Implementation of features took just under 3 hours to complete.

Change list
commit 1cf71eb489750bf779ec34c7e3a72a4cba277a68
Author: Duncan R <duncansrendall@gmail.com>
Date:   Wed Oct 23 11:46:37 2024 +0100

    cleaned up missing member variable initialization and missing function definition

commit a3a545a179e752ebc0e4967113c5f0734e9af1bb
Author: Duncan R <duncansrendall@gmail.com>
Date:   Wed Oct 23 11:37:37 2024 +0100

    added shared brick textures

commit 720910f442d04c56c413fd736f1481c7563c583f
Author: Duncan R <duncansrendall@gmail.com>
Date:   Wed Oct 23 11:26:16 2024 +0100

    added score counter with UI

commit 18f87ecbd553a3fbf35066daa52602938db49c46
Author: Duncan R <duncansrendall@gmail.com>
Date:   Wed Oct 23 11:00:21 2024 +0100

    add toggleable mouse movement with the tab key

commit f374e71185692e61f208c9cf329613f30b4ed109
Author: Duncan R <duncansrendall@gmail.com>
Date:   Wed Oct 23 10:33:01 2024 +0100

    fixed circular dependancy