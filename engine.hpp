#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

#include <exception>
#include <map>
#include <string>
#include <vector>

#ifdef WIN32
#include <GL/glew.h>
#elif __APPLE__
#include <OpenGL/glew.h>
#else
#include <GL3/gl3.h>
#endif

#include <boost/assign/list_of.hpp>

#ifdef WIN32
#include <SDL.h>
#elif __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "eventable.hpp"
#include "glerror.h"
#include "renderable.hpp"
#include "singleton.hpp"
#include "types.h"
#include "updateable.hpp"

using namespace std;

class Engine : public Singleton<Engine> {
	public:
		SDL_Window * _window;
		SDL_GLContext _context;
		map<SDL_GLattr, int> _glAttributes;
		Uint32 _windowFlags;
		string _title;
		int2 _size;
		int2 _pos;
		bool _running;
		uint _targetFPS;
		Uint32 _delayTick, _updateTick;
		vector<Eventable *> _eventHandlers;
		vector<Updateable *> _updateHandlers;
		vector<Renderable *> _renderHandlers;
		

		Engine() :	_title("SDL2.0+OpenGL3.2"),
					_size(1024, 600),
					_glAttributes((const map<SDL_GLattr, int> &)boost::assign::map_list_of(SDL_GL_CONTEXT_MAJOR_VERSION, 3)(SDL_GL_CONTEXT_MINOR_VERSION, 2)(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE)(SDL_GL_DOUBLEBUFFER, 1)),
					_pos(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED),
					_windowFlags(SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE),
					_running(false),
					_targetFPS(1) {
		}

		~Engine() {
			SDL_GL_DeleteContext(_context);
			SDL_DestroyWindow(_window);
			SDL_Quit();
		}

		map<SDL_GLattr, int> & glAttributes(map<SDL_GLattr, int> & attrs) {
			for (map<SDL_GLattr, int>::iterator i = attrs.begin(); i != attrs.end(); ++i) {
				_glAttributes[i->first] = i->second;
			}

			return _glAttributes;
		}

		void setAttributes() {
			for (map<SDL_GLattr, int>::iterator i = _glAttributes.begin(); i != _glAttributes.end(); ++i) {
				SDL_GL_SetAttribute(i->first, i->second);
			}
		}

		void checkAttributes() {
			for (map<SDL_GLattr, int>::iterator i = _glAttributes.begin(); i != _glAttributes.end(); ++i) {
				int value;
				SDL_GL_GetAttribute(i->first, &value);
				if (value != i->second) {throw exception();}
			}
		}

		void init(Uint32 flags = SDL_INIT_EVERYTHING) {
			if (SDL_Init(flags) < 0) {throw SDL_GetError();}

			setAttributes();

			if ((_window = SDL_CreateWindow(_title.c_str(), _pos.x, _pos.y, _size.x, _size.y, _windowFlags)) == NULL) {throw SDL_GetError();}

			if ((_context = SDL_GL_CreateContext(_window)) == NULL) {throw SDL_GetError();}

			glewExperimental=TRUE;
			if(glewInit() != GLEW_OK) {throw exception();}

			checkAttributes();
			if (glError()) {throw exception();}
		}

		string & title(string & title) {
			return _title = title;
		}

		int2 & size(int2 & size) {
			return _size = size;
		}

		void run() {
			reshape();
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			if (glError()) {throw exception();}

			_running = true;
			_delayTick = _updateTick = SDL_GetTicks();
			while (_running) {
				doEvent();
				doUpdate();
				doRender();

				// Timing
				long delta, delay;
				delta = SDL_GetTicks() - _delayTick;
				delay = max<long>((1000 / _targetFPS) - delta, (long)1); // Give the OS a break, always call thread sleep. 1ms even tho the resolution is likely to be >10ms. Max framerate on OS X appears to be ~58 probably due to the resolution.
				SDL_Delay((uint)delay);
				_delayTick = SDL_GetTicks();
			}
		}

		void doEvent() {
			SDL_Event event;
			while (SDL_PollEvent(&event)) { // While there are events waiting
				switch (event.type) {
					case SDL_QUIT: {_running = false;} break; // Handle quit, don't remove this thinking OS X will do it.
					case SDL_WINDOWEVENT: {
						switch (event.window.event) {
							case SDL_WINDOWEVENT_RESIZED: {
								_size = int2(event.window.data1, event.window.data2);
								reshape();
								doRender();
							} break;
						}
					} break;
					case SDL_KEYDOWN: {
						switch (event.key.keysym.sym) {
							case SDLK_ESCAPE: {_running = false;} break;
						}
					} break;
				}

				for (vector<Eventable *>::iterator i = _eventHandlers.begin(); i != _eventHandlers.end(); ++i) {
					(*i)->event(event); // Call event on every registered object
				}
			}
		};

		void doUpdate() {
			Uint32 delta;
			delta = SDL_GetTicks() - _updateTick;
			_updateTick = SDL_GetTicks();		
			for (vector<Updateable *>::iterator i = _updateHandlers.begin(); i != _updateHandlers.end(); ++i) {
				(*i)->update(delta); // Call update on every registered object
			}
		};

		void doRender() {
			glClear(GL_COLOR_BUFFER_BIT);
			if (glError()) {throw exception();}

			for (vector<Renderable *>::iterator i = _renderHandlers.begin(); i != _renderHandlers.end(); ++i) {
				(*i)->render();
			}

			SDL_GL_SwapWindow(_window);
		}

		void reshape() {
			glViewport(0, 0, _size.x, _size.y);
			if (glError()) {throw exception();}
		}

		void addEventHandler(Eventable * obj) {_eventHandlers.push_back(obj);}
		void removeEventHandler(Eventable * obj) {_eventHandlers.erase(remove(_eventHandlers.begin(), _eventHandlers.end(), obj));}
	
		void addUpdateHandler(Updateable * obj) {_updateHandlers.push_back(obj);}
		void removeUpdateHandler(Updateable * obj) {_updateHandlers.erase(remove(_updateHandlers.begin(), _updateHandlers.end(), obj));}
		
		void addRenderHandler(Renderable * obj) {_renderHandlers.push_back(obj);}
		void removeRenderHandler(Renderable * obj) {_renderHandlers.erase(remove(_renderHandlers.begin(), _renderHandlers.end(), obj));}
};

#endif

