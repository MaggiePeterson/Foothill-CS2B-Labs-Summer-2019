// Student ID: 20392644
//  Playlist.cpp
//  Lab1Playlist
//
//  Created by Margaret Peterson on 7/7/19.

//  Copyright © 2019 Margaret Peterson. All rights reserved.
//

#include <stdio.h>

#include "Playlist.h"

bool SongEntry::set_id(int id){
   if(id < 0){
      return false;
   }
   this->id = id;
   return true;
}

bool SongEntry::set_name(string theName){
   if(theName.length() < 1){
      return false;
   }
   this->name = theName;
   return true;

}

PlaylistNode* PlaylistNode::insert_next(PlaylistNode *p){

   this->next = p;

   return p;

}

PlaylistNode* PlaylistNode::remove_next(){

   PlaylistNode* tempNode = this->next;
   this->next = tempNode->next;
   free(tempNode);
   return this;

   return this;

}

PlaylistNode::~PlaylistNode(){
   delete next;

}

Playlist::Playlist(){

   head = new PlaylistNode;
   prevToCurr = head;
   tail = new PlaylistNode;
   size = 0;
}

Playlist::~Playlist(){
   clear();
   delete head;
}


Playlist* Playlist::clear(){
   if(!this->size) //if empty
      return NULL;

   prevToCurr =head;

   while(prevToCurr->get_next() != nullptr){
      prevToCurr->remove_next();
   }
   prevToCurr = head;
   tail = head;
   size = 0;
   return this;

}

Playlist* Playlist::rewind(){

   prevToCurr = head;

   if(prevToCurr != head)
      return nullptr;

   return this;
}

Playlist* Playlist::advance_curr_to_next(){

   if(!this->size || prevToCurr->get_next() == tail){
      return nullptr;
   }

   prevToCurr = get_current_node();
   return this;
}
// doesnt work..
Playlist* Playlist::circular_advance_curr_to_next(){
   if(!this->size)
      return nullptr;

   if((get_current_node() == tail) ) //if last or second last node
      rewind();
   else
      advance_curr_to_next();

    return this;

}

Playlist* Playlist::push_back(PlaylistNode *p){

   if(size == 0){
      head->insert_next(p);
   }
   else {
      tail->insert_next(p);
   }

   tail = p;

   if(tail != p) //if fail
      return nullptr;

     size++;

   return this;

}

Playlist* Playlist::push_front(PlaylistNode *p){

   if(size == 0){
      head->insert_next(p);
      tail =  p;
   }
   else {

      p->insert_next(head->get_next());
      head->insert_next(p); }

   if(head->get_next() != p) //if fail
      return nullptr;



   size++;

   return this;
}

Playlist* Playlist::insert_at_curr(PlaylistNode *p){ //works

   if(p == nullptr)
      return nullptr;

   if(get_current_node() == tail || size == 0) //reset the tail
      tail = p;

   PlaylistNode* tmp = prevToCurr->get_next();
   prevToCurr->insert_next(p);
   p->insert_next(tmp);

    size++;


   return this;

}

Playlist* Playlist::remove_at_curr(){
   if(prevToCurr->get_next() == nullptr ) //if current is null, fail
      return NULL;

   if(prevToCurr->get_next() == tail) //current is tail, reset tail
      tail = prevToCurr;

    prevToCurr->remove_next();

   size--;

   return this;
}

PlaylistNode* Playlist::find_by_id(int id) const{

   PlaylistNode* currNode = head->get_next();
   while(currNode != nullptr){
      if(currNode->get_song().get_id() == id){
         return currNode;
      }
      currNode = currNode->get_next();
   }
   return nullptr;
}

PlaylistNode* Playlist::find_by_song_name(string songname) const{

   PlaylistNode* currNode = head->get_next();
   while(currNode != nullptr){
      if(currNode->get_song().get_name() == songname){
         return currNode;
      }
      currNode = currNode->get_next();
   }

   return nullptr;

}

string Playlist::toString() const{
   PlaylistNode* currNode = head->get_next();
   int id = 0;
   string ID;
   std::stringstream ss;
   string playlist = "Playlist: " + to_string(size) + " entries.\n";
   while(currNode!= nullptr){
      id = currNode->get_song().get_id();

      ss << std::setw(5) << std::setfill('0') << id;
      ID = ss.str();
      ss.str(std::string());

      playlist+= "ID " + ID + ": " + currNode->get_song().get_name() + "\n";
      currNode = currNode->get_next();
   }

   return playlist;

}
