# Void-Leviathan
or, scifi roguelike via libtcod for basic facilities

Even though few people will understand - let's get it out of the way:
Yes, I do love Cyber Knight. In fact, I love Cyber Knight so much, I've decided to make more since nobody else probably will.

There are some obvious differences at this stage of development - for once, CK combat took place on an 8x6 grid separate from the adventure map. It also had a 3-people squad (assembled out of 6 distinct soldiers), each piloting a different machine. Even now I'm torn on whether to follow up on those mechanics as well - on one hand, this tactical combat with all its quirks and challenges like machine composition, melee lock and simultaneous movement are an important part of CK mechanics, on the other hand I don't want to just blindly ape the classic, and roguelike is not a great vessel for this style of gameplay anyway. So, perhaps in the future? Perhaps in a sequel that will not be a roguelike? Perhaps.

# Overview
So, what are the main features of Void Leviathan?

The intention is to create a relatively fast paced roguelike heavy on ranged combat.

Player character is sitting inside a combat robot. There are six different robots to choose from that can be swapped and kitted out freely outside of a mission. Each robot has strengths and weaknesses, and can equip different classes of both weapons (powered by reactor) and options (disposable / limited ammo). Each robot can have several chosen weapons stowed and swapped during mission as the situation changes and needs arise.

While the player character accumulates experience that will in part decide their combat performance, the key upgrade / growth system will be the "Neopart" system (name shamelessly stolen and provisional until I have a good term). Each enemy has a small chance of dropping its "Neopart". Said part will be analyzed after completing a mission, and will either provide a pernament boost to one stat of all player robots, or will create an entirely new weapon for future use.

At this point in time, the maps will *probably* be non-persistent. Right now I just don't see much of a need to create persistent maps though I do intend to implement more map generation styles as well as some features I have had in mind since my previous aborted RL attempt (that I'm scavenging and salvaging for this one).

# Acknowledgements

This project utilizes libtcod, an incredibly useful roguelike development library. It is currently hosted here: https://github.com/libtcod/libtcod

Quite a few routines are and likely will be backported from Richard D Clark's fantastic roguelike tutorial for FreeBasic. You can find it here: http://users.freebasic-portal.de/rdc/tutorials.html

Cyber Knight was released in 1990 for PC Engine and in 1992 for Super Famicom by SNE group / Tokinhouse. While it never officially made it outside of Japan, it has a great fanmade English translation by AGTP. A sequel also exists, likewise fantranslated.
