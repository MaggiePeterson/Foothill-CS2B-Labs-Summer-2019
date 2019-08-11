//
//  main.cpp
//  Lab1Playlist
//
//  Created by Margaret Peterson on 7/7/19.
//  Copyright © 2019 Margaret Peterson. All rights reserved.
//

#include <iostream>
#include "Playlist.h"
using namespace std;

int main(int argc, const char * argv[]) {

   Playlist play;
   SongEntry song;
   song.set_name("song1");
   song.set_id(1);
   SongEntry song1;
   song1.set_name("song2");
   song1.set_id(22);
   SongEntry song3;
   song3.set_name("song3");
   song3.set_id(33);
   SongEntry song4;
   song4.set_name("song4");
   song4.set_id(44);

   PlaylistNode* node3 = new PlaylistNode(song3);
   PlaylistNode* node1 = new PlaylistNode(song);
   PlaylistNode* node2 = new PlaylistNode(song1);
   PlaylistNode* node4 = new PlaylistNode(song4);

   play.push_back(node3);
   play.push_back(node2);
   play.circular_advance_curr_to_next();
   play.circular_advance_curr_to_next();
   play.remove_at_curr();


   cout<<play.toString()<<endl;


   return 0;
}
