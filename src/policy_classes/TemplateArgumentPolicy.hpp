#include <srcSAXEventDispatch.hpp>
#include <srcSAXHandler.hpp>

#include <exception>

#ifndef INCLUDED_TYPE_POLICY_HPP
#define INCLUDED_TYPE_POLICY_HPP

class NamePolicy;
class TemplateArgumentPolicy : public srcSAXEventDispatch::EventListener, public srcSAXEventDispatch::PolicyDispatcher, public srcSAXEventDispatch::PolicyListener {

public:
    enum TemplateArgumentType { NAME, LITERAL, OTHER };

    struct TemplateArgumentData {
        std::vector<std::pair<void *, TemplateArgumentType>> templateArgument;

        friend std::ostream & operator<<(std::ostream & out, const TemplateArgumentData & argumentData);

    };
    private:
        TemplateArgumentData data;
        std::size_t argumentDepth;

        NamePolicy * namePolicy;

    public:
        TemplateArgumentPolicy(std::initializer_list<srcSAXEventDispatch::PolicyListener *> listeners = {});
        virtual void Notify(const PolicyDispatcher * policy, const srcSAXEventDispatch::srcSAXEventContext & ctx) override;
    protected:
        virtual void * DataInner() const override;
    private:
        void InitializeTemplateArgumentPolicyHandlers();

        void CollectNamesHandler();
        void CollectModifersHandler();
        void CollectSpecifiersHandler();

};

#endif