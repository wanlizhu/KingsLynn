#include "Wanlix/Core3D/Platform/Window.h"

namespace Wanlix
{
    Window::Window()
    {}

    SurfaceType Window::GetSurfaceType() const
    {
        return SurfaceType::DesktopWindow;
    }

    bool Window::AdaptForVideoMode(const VideoModeDescriptor& videoModeDesc)
    {
        /* Query current window descriptor */
        auto windowDesc = GetDescriptor();

        /* Adapt window size and position */
        windowDesc.size = videoModeDesc.resolution;

        if (videoModeDesc.fullscreen)
        {
            windowDesc.borderless = true;
            windowDesc.position = { 0, 0 };
        }
        else
        {
            windowDesc.borderless = false;
            windowDesc.centered = true;
        }

        /* Set new window descriptor and return with success */
        SetDescriptor(windowDesc);

        return true;
    }

    bool Window::Tick()
    {
        ProcessEventsInternal();
        return !mQuitFlag;
    }

    Display::UniquePtr Window::GetResidentDisplay() const
    {
        auto displayList = Display::List();

        const auto winPos = GetPosition();
        const auto winSize = GetContentSize();
        const auto winArea = static_cast<int>(winSize.width * winSize.height);

        for (auto& display : displayList)
        {
            auto offset = display->GetOffset();
            auto extent = display->GetDisplayMode().resolution;

            int scrX = static_cast<int>(extent.width);
            int scrY = static_cast<int>(extent.height);

            /* Calculate window boundaries relative to the current display */
            int x1 = winPos.x - offset.x;
            int y1 = winPos.y - offset.y;
            int x2 = x1 + static_cast<int>(winSize.width);
            int y2 = y1 + static_cast<int>(winSize.height);

            /* Is window fully or partially inside the dispaly? */
            if (x2 >= 0 && x1 <= scrX &&
                y2 >= 0 && y1 <= scrY)
            {
                /* Is at least the half of the window inside the display? */
                x1 = std::max(0, x1);
                y1 = std::max(0, y1);

                x2 = std::min(x2 - x1, scrX);
                y2 = std::min(y2 - y1, scrY);

                auto visArea = x2 * y2;

                if (visArea * 2 >= winArea) {
                    return std::move(display);
                }
            }
        }

        return nullptr;
    }

    void Window::AddEventListener(Listener listener)
    {
        mEventListeners.push_back(listener);
    }

    void Window::RemoveEventListener(Listener listener)
    {
        auto it = std::find(mEventListeners.begin(), mEventListeners.end(), listener);
        if (it != mEventListeners.end()) {
            mEventListeners.erase(it);
        }
    }

    void Window::PostEvent(Event event, std::any arg1, std::any arg2)
    {
        for (auto& listener : mEventListeners) {
            switch (event) {
            case Event::Redraw:
                listener->OnRedraw(*this);
                break;
            case Event::Quit:
                listener->OnQuit(*this);
                break;
            case Event::KeyDown:
                listener->OnKeyDown(*this, std::any_cast<Key>(arg1));
                break;
            case Event::KeyUp:
                listener->OnKeyUp(*this, std::any_cast<Key>(arg1));
                break;
            case Event::DoubleClick:
                listener->OnDoubleClick(*this, std::any_cast<Key>(arg1));
                break;
            case Event::Char:
                listener->OnChar(*this, std::any_cast<wchar_t>(arg1));
                break;
            case Event::WheelMotion:
                listener->OnWheelMotion(*this, std::any_cast<int>(arg1));
                break;
            case Event::LocalMotion: {
                Offset offset(std::any_cast<uint32_t>(arg1), std::any_cast<uint32_t>(arg2));
                listener->OnLocalMotion(*this, offset);
                break;
            }
            case Event::GlobalMotion: {
                Offset offset(std::any_cast<uint32_t>(arg1), std::any_cast<uint32_t>(arg2));
                listener->OnGlobalMotion(*this, offset);
                break;
            }
            case Event::Resize: {
                Extent extent(std::any_cast<uint32_t>(arg1), std::any_cast<uint32_t>(arg2));
                listener->OnResize(*this, extent);
                break;
            }
            default:
                break;
            }
        }
    }
}