#ifndef HANDLERS_HPP_INCLUDE
#define HANDLERS_HPP_INCLUDE

#include <map>
#include <string>
#include <iostream>
#include "../header/Taste.h"

#include "../server/server.hpp"

class HomePageHandler : public RequestHandler {
public:
    HomePageHandler(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class RegisterHandler : public RequestHandler {
public:
    RegisterHandler(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class LoginHandler : public RequestHandler {
public:
    LoginHandler(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class ShowPlaylists : public RequestHandler {
public:
    ShowPlaylists(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class AddToPlaylist : public RequestHandler {
public:
    AddToPlaylist(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class ShowAccounts : public RequestHandler {
public:
    ShowAccounts(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class ShowUserDetail : public RequestHandler {
public:
    ShowUserDetail(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class ShowSongDetail : public RequestHandler {
public:
    ShowSongDetail(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class ShowPlaylistDetail : public RequestHandler {
public:
    ShowPlaylistDetail(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class FollowUnfollow : public RequestHandler {
public:
    FollowUnfollow(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class DeleteSong : public RequestHandler {
public:
    DeleteSong(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class DeletePlaylist : public RequestHandler {
public:
    DeletePlaylist(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class Like : public RequestHandler {
public:
    Like(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class Search : public RequestHandler {
public:
    Search(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class LogoutHandler : public RequestHandler {
public:
    LogoutHandler(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class SignupHandler : public RequestHandler {
public:
    SignupHandler(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class SearchResult : public RequestHandler {
public:
    SearchResult(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class Recommendation : public RequestHandler {
public:
    Recommendation(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class UploadHandler : public RequestHandler {
public:
    UploadHandler(Taste* uTaste_,Server* Myserver);
    Response* callback(Request*);
private:
    Taste* uTaste;
    Server* myserver;
};

class ShowArtistSongs : public RequestHandler {
public:
    ShowArtistSongs(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class PlaylistHandler : public RequestHandler {
public:
    PlaylistHandler(Taste* uTaste_);
    Response* callback(Request* req);
private:
    Taste* uTaste;
};

#endif // HANDLERS_HPP_INCLUDE
