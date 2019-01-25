#pragma once

#include "Context.h"
#include "Channel.h"
#include "Node.h"

namespace Gadgetron::Grappa {

    class WeightsCalculator : public Core::TypedGadgetNode<Core::Acquisition> {
    public:
        WeightsCalculator(const Core::Context &, const std::unordered_map<std::string, std::string> &);

        NODE_PROPERTY(target_coils, int, "Number of target coils for GRAPPA recon", 0);

        // TODO: This doesn't need to be special? We can handle all of it in 'uncombined_channels'?
        NODE_PROPERTY(uncombined_channels, std::string, "Uncombined channels (as a comma separated list of channel indices", "");
        NODE_PROPERTY(uncombined_channels_by_name, std::string, "Uncombined channels (as a comma separated list of channel names", "");

        // TODO: Get rid of these pointless things.
        NODE_PROPERTY(device_channels, int, "Number of device channels", 0);


        void process(Core::TypedInputChannel<Core::Acquisition> &in, Core::OutputChannel &out) override;

    private:
        const Core::Context context;
    };
}
