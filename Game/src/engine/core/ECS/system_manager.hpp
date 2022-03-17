#pragma once
#include "system.hpp"
#include "../types.hpp"
#include <memory>
#include <unordered_map>

namespace brown {
    class system_manager {
        public:
            template<typename T>
            std::shared_ptr<T> register_system() {
                const char *type_name = typeid(T).name();

                auto system = std::make_shared<T>();
                m_systems.insert({type_name, system});
                return system;
            }

            template<typename T>
            void set_signature(signature signature) {
                const char* type_name = typeid(T).name();

                m_signatures.insert({type_name, signature});
            }

            void entity_destroyed(entity_id entity) {
                for (auto const& pair: m_systems) {
                    auto const& system = pair.second;

                    system->m_entities.erase(entity);
                }
            }

            void entity_signature_changed(entity_id entity, signature signature) {
                for(auto const& pair: m_systems) {
                    auto const& type = pair.first;
                    auto const& system = pair.second;
                    auto const& sys_signature = m_signatures[type];

                    if((signature & sys_signature) == sys_signature)
                        system->m_entities.insert(entity);
                    else
                        system->m_entities.erase(entity);
                }
            }
        
        private:
            std::unordered_map<const char*, signature> m_signatures{};
            std::unordered_map<const char*, std::shared_ptr<system>> m_systems{};
    };
}