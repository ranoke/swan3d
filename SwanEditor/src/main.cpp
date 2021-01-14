#define SWAN_ENTRY_POINT
#include "Swan.h"
#include "EditorLayer.h"

namespace Swan
{

class Editor : public Application
{
public:
    Editor()
    {
        PushLayer(new EditorLayer);
    }

    ~Editor()
    {

    }
};




}

Swan::Application* Swan::CreateApplication()
{
    return new Swan::Editor();
}
