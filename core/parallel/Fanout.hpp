#pragma once

namespace Gadgetron::Core::Parallel {

    template<class... ARGS>
    Fanout<ARGS...>::Fanout(
            const Context &context,
            const GadgetProperties &props
    ) : TypedBranch<ARGS...>(props) {}


    template<class... ARGS>
    void Fanout<ARGS...>::process(TypedInputChannel<ARGS...> &input, std::map<std::string, OutputChannel> output) {
        for (auto thing : input) {

            GINFO_STREAM("Oh, a thing!");

            for (auto &pair : output) {
                auto copy_of_thing = thing;
                pair.second.push(copy_of_thing);
            }

            sleep(1);
        }
    }
}
