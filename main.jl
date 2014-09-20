module SDL
    libtest = dlopen(string(pwd(),"/libtest.so"))    
    function sdl_init()
        ccall( dlsym(libtest, :init), Void, ())
    end
    function getwindow()
        return ccall( dlsym(libtest, :getwindow), Ptr{Void}, ())
    end
    function getrenderer(window, width, height)
        return ccall( dlsym(libtest, :getrenderer), Ptr{Void}, (Ptr{Void}, Int32, Int32), window, width, height);
    end
    function getsurface(path)
        return ccall( dlsym(libtest, :getsurface), Ptr{Void}, (Ptr{Uint8},), path)
    end
    function gettexture(renderer::Ptr{Void}, path)
        return ccall( dlsym(libtest, :gettexture), Ptr{Void}, (Ptr{Void}, Ptr{Uint8}), renderer, path)
    end    
    function render(renderer, texture, x, y)
        ccall( dlsym(libtest, :render), Void, (Ptr{Void}, Ptr{Void}, Int32, Int32), renderer, texture, x, y)
    end
    function renderagent(renderer, texture, x, y, angle)
        # if ccall( dlsym(libtest, :checkcollision), ) == 1:
            ccall( dlsym(libtest, :renderagent), Void, (Ptr{Void}, Ptr{Void}, Int32, Int32, Float64), renderer, texture, x, y, angle)
    end    
    # function checkcollision(agent, background, x, y)
    #     ccall( dlsym(libtest, :checkcollision), Int32, (agent, background, x, y), Ptr{Void}, Ptr{Void}, Int32, Int32)
    # end
    function sdl_getevents()
        return ccall( dlsym(libtest, :get_events), Ptr{Void}, ())
    end    
    function quit(window)
        ccall( dlsym(libtest, :quit), Void, (Ptr{Void},), window)
    end    
    function sdl_events(events::Ptr{Void})
        return ccall( dlsym(libtest, :sdl_events), Int32, (Ptr{Void},), events);
    end
    function setpixel(map::Ptr{Void}, x, y, r, g, b)
        ccall( dlsym(libtest, :setpixel), Int32, (Ptr{Void}, Int32, Int32, Uint8, Uint8, Uint8), map, x, y, r, g, b);
    end
    function update(src::Ptr{Void})
        ccall( dlsym(libtest, :update), Void, (Ptr{Void},), src);
    end
    export sdl_init, quit, getwindow, getrenderer, gettexture, getsurface, setpixel, update,
          sdl_events, sdl_getevents, render, renderagent, libtest
end

tic();
using SDL


width = 1000
height = 1000

sdl_init();
window = getwindow()
renderer = getrenderer(window, width, height);
background_surface = getsurface("starmaze.bmp")
background_texture = gettexture(renderer, "starmaze.bmp")
agent = gettexture(renderer, "agent.bmp")
events = sdl_getevents();

# i = 0.0

# while sdl_events(events) == 1 
for i = 0.0:0.001:20*pi
    x = int32(450+250*cos(i))
    y = int32(450+250*sin(i))
    render(renderer, background_texture, 0, 0)
    a = ccall( dlsym(libtest, :checkcollision), Int32, (Ptr{Void}, Ptr{Void}, Int32, Int32), agent, background_surface, x, y)
    # println(a)
    renderagent(renderer, agent, x, y, 360.0*cos(i))
    update(renderer)
end

quit(window)
toc();