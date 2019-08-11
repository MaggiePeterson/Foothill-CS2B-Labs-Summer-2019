// Student ID: 20392644
//  Playlist.h
//  Lab1Playlist
//
//  Created by Margaret Peterson on 7/7/19.
//  Copyright © 2019 Margaret Peterson. All rights reserved.
//

#include <string>
using namespace std;
#include <sstream>
#include <iomanip>
class SongEntry{

private:
   int id;
   string name;

public:
   SongEntry(int theId =0, string theName = "Unnamed") : id(theId), name(theName) {}
   int get_id() const {return id;}
   string get_name() const {return name;}

   bool set_id(int id);
   bool set_name(string theName);

   friend class Tests;
};

class PlaylistNode{

private:
   SongEntry song;
   PlaylistNode* next;

public:
   PlaylistNode(const SongEntry& theSong=SongEntry()): song(theSong), next(nullptr) {}
   ~PlaylistNode();

   SongEntry get_song() const {return song;}
   PlaylistNode* get_next() const {return next;}

   PlaylistNode* insert_next(PlaylistNode *p);
   PlaylistNode* remove_next();

   friend class Tests;

};



class Playlist {


public:
   int size;

   PlaylistNode *head, *tail, *prevToCurr;

   Playlist();
   ~Playlist();

   int get_size() const {return size;}
   PlaylistNode* get_current_node()  const {return prevToCurr->get_next();}

   Playlist* clear();
   Playlist* rewind();
   Playlist* advance_curr_to_next();
   Playlist* circular_advance_curr_to_next();

   Playlist* push_back(PlaylistNode *p);
   Playlist* push_front(PlaylistNode *p);
   Playlist* insert_at_curr(PlaylistNode *p);
   Playlist *remove_at_curr();

   PlaylistNode *find_by_id(int id) const;
   PlaylistNode *find_by_song_name(string songname) const;

   string toString() const;
   friend class Tests;

};


