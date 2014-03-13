/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 * Version 0.6b
 *
 * Copyright (c) 2012-2014 Inviwo Foundation
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met: 
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * Main file authors: Timo Ropinski, Sathish Kottravel, Erik Sund�n
 *
 *********************************************************************************/

#ifndef IVW_PROCESSORNETWORK_H
#define IVW_PROCESSORNETWORK_H

#include <inviwo/core/common/inviwo.h>
#include <inviwo/core/common/inviwocoredefine.h>
#include <inviwo/core/processors/processor.h>
#include <inviwo/core/processors/processorobserver.h>
#include <inviwo/core/network/portconnection.h>
#include <inviwo/core/network/processornetworkobserver.h>
#include <inviwo/core/links/processorlink.h>
#include <inviwo/core/links/linkevaluator.h>
#include <inviwo/core/util/observer.h>
#include <inviwo/core/util/exception.h>

namespace inviwo {

/**
 * This class manages the current processor network. It can be thought of as a container of
 * Processor instances, which Port instances are connected through PortConnection instances,
 * and which Property instances are linked through ProcessorLink instances. To manage Processors,
 * PortConnections and ProcessorLinks, add and remove methods are available for all
 * these entities. The network should be only modified by using these methods. Typically,
 * these methods are called by the NetworkEditor, which enables the user to edit
 * ProcessorNetworks.
 *
 * When the PorcessorNetwork has been changed, it is flagged as modified. This mechanism is
 * used by the ProcessorNetworkEvaluator to identify if the ProcessorNetwork needs to be
 * analyzed before processing.
 *
 * In the model view controller design pattern, the ProcessorNetwork represents the model,
 * which means that no graphical representations are generated for the added entities. Adding
 * and removing of the graphical representations is done in the NetworkEditor.
 */
class IVW_CORE_API ProcessorNetwork : public IvwSerializable, public ProcessorNetworkObservable, public ProcessorObserver {

public:

    ProcessorNetwork();
    virtual ~ProcessorNetwork();

    /**
     * Adds a Processor to the ProcessorNetwork. The identifiers of all processors in the
     * ProcessorNetwork should be unique.
     *
     * @param[in] processor The Processor to be added.
     * @see removeProcessor(), Processor::setIdentifier()
     */
    void addProcessor(Processor* processor);

    /**
     * Removes a Processor from the ProcessorNetwork. To ensure that the network does not end up
     * in a corrupt state, this method first removes and deletes all PortConnections and ProcessorLinks, which
     * are related to the Processor to be removed.
     *
     * @param[in] processor The Processor to be removed.
     * @see addProcessor()
     */
    void removeProcessor(Processor* processor);

    /**
    * Removes and deletes a Processor from the ProcessorNetwork. To ensure that the network does not end up
    * in a corrupt state, this method first removes and deletes all PortConnections and ProcessorLinks, which
    * are related to the Processor to be removed.
    *
    * @param[in] processor The Processor to be removed.
    * @see addProcessor()
    */
    void removeAndDeleteProcessor(Processor* processor);

    /**
    * Returns the Processor from the ProcessorNetwork, which has the given identifier.
    * In case no Processor with the given identifier is contained in the network, a null
    * pointer is returned.
    *
    * @param identifier Identifier of the Processor to be accessed.
    * @see getProcessorsByType(), Processor::setIdentifier(), Processor::getIdentifier()
    */
    Processor* getProcessorByName(std::string identifier) const;

    /**
    * Returns a vector of Processors which are of type T. In case no Processors match T
    * an empty vector is returned.
    *
    * @see getProcessorByName()
    */
    template<class T> std::vector<T*> getProcessorsByType() const;

    /**
    * Returns a vector of all Processors.
    *
    * @return A vector of Processors
    */
    std::vector<Processor*> getProcessors() const;


    /**
    * Adds a PortConnection to the ProcessorNetwork. This involves creating the connection
    * between the two specified ports, as well as adding this connection to the ProcessorNetwork.
    *
    * @param[in] sourcePort The outport.
    * @param[in] destPort The inport.
    * @return The newly created connection. NULL if a connection could not be made.
    * @see removeConnection()
    */
    PortConnection* addConnection(Outport* sourcePort, Inport* destPort);

    /**
     * Removes and deletes a PortConnection from the ProcessorNetwork. This involves resolving the connection
     * between the two specified Ports, as well as removing this connection from the
     * ProcessorNetwork.
     *
     * @param[in] sourcePort The outport.
     * @param[in] destPort The inport.
     * @see addConnection()
     */
    void removeConnection(Outport* sourcePort, Inport* destPort);

    /**
    * Checks weather two port are connected
    *
    * @param[in] sourcePort The outport.
    * @param[in] destPort The inport.
    * @return Weather the two port are connected
    * @see addConnection()
    */
    bool isConnected(Outport* sourcePort, Inport* destPort);

    /**
    * Get a connection between two ports
    *
    * @param[in] sourcePort The outport.
    * @param[in] destPort The inport.
    * @return The PortConnection between the ports or NULL if there is none.
    * @see addConnection()
    */
    PortConnection* getConnection(Outport* sourcePort, Inport* destPort);

    /**
    * Returns a vector of all Connections.
    *
    * @return A vector of Connections
    */
    std::vector<PortConnection*> getConnections() const;


    /**
    * Adds a ProcessorLink to the ProcessorNetwork. This involves creating the link
    * between the two specified processors, as well as adding this connection to the ProcessorNetwork.
    *
    * @param[in] sourceProcessor The source processor.
    * @param[in] destProcessor The destination processor.
    * @return The newly crated link.
    * @see removeConnection()
    */
    ProcessorLink* addLink(Processor* sourceProcessor, Processor* destProcessor);

    /**
    * Removes and deletes a PortConnection from the ProcessorNetwork. This involves resolving the connection
    * between the two specified Ports, as well as removing this connection from the
    * ProcessorNetwork.
    *
    * @param[in] sourceProcessor The source processor.
    * @param[in] destProcessor The destination processor.
    * @see addConnection()
    */
    void removeLink(Processor* sourceProcessor, Processor* destProcessor);

    /**
    * Checks weather the two processors have a link
    *
    * @param[in] sourceProcessor The source processor.
    * @param[in] destProcessor The destination processor.
    * @return Weather the two processors have a link.
    * @see addConnection()
    */
    bool isLinked(Processor* src, Processor* dst);

    /**
    * Get a link between two processors
    *
    * @param[in] sourceProcessor The source processor.
    * @param[in] destProcessor The destination processor.
    * @return The link between the processors or NULL if there is none.
    * @see addConnection()
    */
    ProcessorLink* getLink(Processor* sourceProcessor, Processor* destProcessor) const;

    /**
    * Returns a vector of all Links.
    *
    * @return A vector of Links
    */
    std::vector<ProcessorLink*> getLinks() const;

    void modified();
    void setModified(bool modified);
    bool isModified() const;

    bool isInvalidating() const;
    void onAboutPropertyChange(Property*);
    void onProcessorInvalidationBegin(Processor*);
    void onProcessorInvalidationEnd(Processor*);
    void onProcessorRequestEvaluate(Processor* p = NULL);
    Processor* getInvalidationInitiator();

    inline void lock() { locked_++; }
    inline void unlock() { (locked_>0)?locked_--:locked_=0; }
    inline bool islocked() const { return (locked_!=0); }

    virtual void serialize(IvwSerializer& s) const;
    virtual void deserialize(IvwDeserializer& d) throw (Exception);

    bool isDeserializing()const;

    /**
    * Clears the network objects processors, port connections, processor links etc.,
    * This function clears only the core objects and mainly used to abort any
    * further operation.
    */
    void clear();


private:
    //Property Linking support
    std::vector<ProcessorLink*> getSortedProcessorLinksFromProperty(Property* modifiedProperty);
    void performLinkingOnPropertyChange(Property* modifiedProperty);
    void evaluatePropertyLinks(Property*);

    bool modified_;
    unsigned int locked_;

    std::vector<Processor*> processors_;
    std::vector<PortConnection*> portConnections_;
    std::vector<ProcessorLink*> processorLinks_;

    bool deserializing_;
    bool invalidating_;
    Processor* invalidationInitiator_;
    LinkEvaluator* linkEvaluator_;

    bool evaluationQueued_;

    bool linking_;
    Processor* linkInvalidationInitiator_;
};

template<class T>
std::vector<T*> ProcessorNetwork::getProcessorsByType() const {
    std::vector<T*> processors;

    for (size_t i=0; i<processors_.size(); i++) {
        T* processor = dynamic_cast<T*>(processors_[i]);

        if (processor) processors.push_back(processor);
    }

    return processors;
}

} // namespace

#endif // IVW_PROCESSORNETWORK_H
