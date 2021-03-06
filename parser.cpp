#include "parser.h"
#include "transition.h"

void Parser::set_input(std::vector<Name> input) {
    m_in = input;
    // add the terminating token
    m_in.push_back(Name(TERM_NAME, NameType::TERM));
    // set the current token to the beginning
    m_curr_name = m_in.begin();
    // map the current token to an event
    m_curr_event = to_event(*m_curr_name);
}

Node* Parser::get_output() const {
    return m_root;
}

Event Parser::to_event(const Name& name) {
    switch (name.get_type()) {
    case NameType::LEFT_PAR:
        return Event::LEFT_PAR;
        break;
    case NameType::RIGHT_PAR:
        return Event::RIGHT_PAR;
        break;
    case NameType::IDENT:
        return Event::IDENT;
        break;
    case NameType::NUM:
        return Event::NUM;
        break;
    case NameType::STR:
        return Event::STR;
        break;
    case NameType::TERM:
        return Event::END;
        break;
    default:
        return Event::UNDEF;
        break;
    }
}

Parser::Parser()
    : DFSM(),
    // initializing root of the parsing tree
    m_root(new Node(new Name(INIT_NAME, NameType::INIT)))
{
    m_curr_node = m_root;

    // create transition table
    m_transit_table[State::INIT][Event::LEFT_PAR] = new Transition(new Skip_AddOp(this), State::INIT);
    m_transit_table[State::INIT][Event::RIGHT_PAR] = new Transition(new GoToParent(this), State::INIT);
    m_transit_table[State::INIT][Event::IDENT] = new Transition(new AddArg(this), State::INIT);
    m_transit_table[State::INIT][Event::NUM] = new Transition(new AddArg(this), State::INIT);
    m_transit_table[State::INIT][Event::STR] = new Transition(new AddArg(this), State::INIT);
    m_transit_table[State::INIT][Event::UNDEF] = new Transition(new Err_UndefName(this), State::INIT);
    m_transit_table[State::INIT][Event::END] = new Transition(new NoAction(), State::TERM);
}