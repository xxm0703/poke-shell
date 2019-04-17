#include "shell_ui/scene.hh"

#include <memory>
#include <string>
#include <stdexcept>

#include "ncurses_helper/ncurses_object.hh"

using terminal_user_interface::ncurses_helper::NCursesObject;

namespace terminal_user_interface {
    namespace shell_ui {
        Scene::~Scene() noexcept {
        }

        std::shared_ptr<NCursesObject> Scene::get_scene_object(
                const std::string& name) const {
            return scene_objects_.at(name);
        }

        void Scene::add_scene_object(const std::string& name, 
                std::shared_ptr<NCursesObject> scene_object) {
            if (scene_objects_.find(name) != scene_objects_.end())
                throw std::runtime_error("scene object already exists");
            scene_objects_.insert(std::make_pair(name, scene_object));
        }
    }  // namespace shell_ui
}  // namespace terminal_user_interface

