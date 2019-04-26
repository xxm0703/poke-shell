#ifndef TERMINAL_USER_INTERFACE__SHELL_UI__SCENE_HH
#define TERMINAL_USER_INTERFACE__SHELL_UI__SCENE_HH

#include <memory>
#include <string>
#include <unordered_map>

#include "ncurses_helper/ncurses_object.hh"

namespace terminal_user_interface {
    namespace shell_ui {
        class Scene {
            using scene_objects_map_t = std::unordered_map<std::string, 
                  std::shared_ptr<ncurses_helper::NCursesObject>>;

        public:
            virtual ~Scene() noexcept;
            virtual void init() = 0;
            virtual void update() = 0;
            virtual void destroy() = 0;
            std::shared_ptr<ncurses_helper::NCursesObject> get_scene_object(
                    const std::string&) const;
        protected:
            void add_scene_object(const std::string&, 
                    std::shared_ptr<ncurses_helper::NCursesObject>);
            // TODO: is this even useful
            scene_objects_map_t& all_scene_objects() noexcept;
        private:
            scene_objects_map_t scene_objects_;
        };  // class Scene
    }  // namespace shell_ui
}  // namespace terminal_user_interface

#endif

