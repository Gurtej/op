/*

 Copyright (c) 2013, SMB Phone Inc.
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 The views and conclusions contained in the software and documentation are those
 of the authors and should not be interpreted as representing official policies,
 either expressed or implied, of the FreeBSD Project.

 */

#include <hookflash/stack/internal/stack_Factory.h>

#include <zsLib/Log.h>

namespace hookflash { namespace stack { ZS_DECLARE_SUBSYSTEM(hookflash_stack) } }

namespace hookflash
{
  namespace stack
  {
    namespace internal
    {
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      #pragma mark
      #pragma mark (helper)
      #pragma mark

      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      #pragma mark
      #pragma mark Factory
      #pragma mark

      //-----------------------------------------------------------------------
      void Factory::override(FactoryPtr override)
      {
        singleton()->mOverride = override;
      }

      //-----------------------------------------------------------------------
      FactoryPtr &Factory::singleton()
      {
        static FactoryPtr global = Factory::create();
        if (global->mOverride) return global->mOverride;
        return global;
      }

      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      #pragma mark
      #pragma mark Factory => (internal)
      #pragma mark

      //-----------------------------------------------------------------------
      FactoryPtr Factory::create()
      {
        return FactoryPtr(new Factory);
      }

      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      #pragma mark
      #pragma mark IAccountFactory
      #pragma mark

      //-----------------------------------------------------------------------
      IAccountFactory &IAccountFactory::singleton()
      {
        return *(Factory::singleton().get());
      }

      //-----------------------------------------------------------------------
      AccountPtr IAccountFactory::create(
                                         IAccountDelegatePtr delegate,
                                         IServicePeerContactSessionPtr peerContactSession
                                         )
      {
        return Account::create(delegate, peerContactSession);
      }
      
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      #pragma mark
      #pragma mark IAccountFinderFactory
      #pragma mark

      //-----------------------------------------------------------------------
      IAccountFinderFactory &IAccountFinderFactory::singleton()
      {
        return *(Factory::singleton().get());
      }

      //-----------------------------------------------------------------------
      AccountFinderPtr IAccountFinderFactory::create(
                                                     IAccountFinderDelegatePtr delegate,
                                                     AccountPtr outer
                                                     )
      {
        return AccountFinder::create(delegate, outer);
      }

      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      #pragma mark
      #pragma mark IAccountPeerLocationFactory
      #pragma mark

      //-----------------------------------------------------------------------
      IAccountPeerLocationFactory &IAccountPeerLocationFactory::singleton()
      {
        return *(Factory::singleton().get());
      }

      //-----------------------------------------------------------------------
      AccountPeerLocationPtr IAccountPeerLocationFactory::create(
                                                                 IAccountPeerLocationDelegatePtr delegate,
                                                                 AccountPtr outer,
                                                                 const LocationInfo &locationInfo
                                                                 )
      {
        return AccountPeerLocation::create(delegate, outer, locationInfo);
      }

      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      #pragma mark
      #pragma mark IBootstrappedNetworkFactory
      #pragma mark

      //-----------------------------------------------------------------------
      IBootstrappedNetworkFactory &IBootstrappedNetworkFactory::singleton()
      {
        return *(Factory::singleton().get());
      }

      //-----------------------------------------------------------------------
      BootstrappedNetworkPtr IBootstrappedNetworkFactory::prepare(
                                                                  const char *domain,
                                                                  IBootstrappedNetworkDelegatePtr delegate
                                                                  )
      {
        return BootstrappedNetwork::prepare(domain, delegate);
      }

      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      #pragma mark
      #pragma mark IBootstrappedNetworkFactory
      #pragma mark

      //-----------------------------------------------------------------------
      IBootstrappedNetworkManagerFactory &IBootstrappedNetworkManagerFactory::singleton()
      {
        return *(Factory::singleton().get());
      }

      //-----------------------------------------------------------------------
      BootstrappedNetworkManagerPtr IBootstrappedNetworkManagerFactory::createBootstrappedNetworkManager()
      {
        return BootstrappedNetworkManager::create();
      }

      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      #pragma mark
      #pragma mark IMessageIncomingFactory
      #pragma mark

      //-----------------------------------------------------------------------
      IMessageIncomingFactory &IMessageIncomingFactory::singleton()
      {
        return *(Factory::singleton().get());
      }

      //-----------------------------------------------------------------------
      MessageIncomingPtr IMessageIncomingFactory::create(
                                                         AccountPtr account,
                                                         LocationPtr location,
                                                         message::MessagePtr message
                                                         )
      {
        return MessageIncoming::create(account, location, message);
      }

      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      #pragma mark
      #pragma mark IMessageMonitorFactory
      #pragma mark

      //-----------------------------------------------------------------------
      IMessageMonitorFactory &IMessageMonitorFactory::singleton()
      {
        return *(Factory::singleton().get());
      }

      //-----------------------------------------------------------------------
      MessageMonitorPtr IMessageMonitorFactory::monitor(
                                                        IMessageMonitorDelegatePtr delegate,
                                                        message::MessagePtr requestMessage,
                                                        Duration timeout
                                                        )
      {
        return MessageMonitor::monitor(delegate, requestMessage, timeout);
      }

      //-----------------------------------------------------------------------
      MessageMonitorPtr IMessageMonitorFactory::monitorAndSendToLocation(
                                                                         IMessageMonitorDelegatePtr delegate,
                                                                         ILocationPtr peerLocation,
                                                                         message::MessagePtr message,
                                                                         Duration timeout
                                                                         )
      {
        return MessageMonitor::monitorAndSendToLocation(delegate, peerLocation, message, timeout);
      }

      //-----------------------------------------------------------------------
      MessageMonitorPtr IMessageMonitorFactory::monitorAndSendToService(
                                                                        IMessageMonitorDelegatePtr delegate,
                                                                        IBootstrappedNetworkPtr bootstrappedNetwork,
                                                                        const char *serviceType,
                                                                        const char *serviceMethodName,
                                                                        message::MessagePtr message,
                                                                        Duration timeout
                                                                        )
      {
        return MessageMonitor::monitorAndSendToService(delegate, bootstrappedNetwork, serviceType, serviceMethodName, message, timeout);
      }

      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      #pragma mark
      #pragma mark IMessageMonitorManagerFactory
      #pragma mark

      //-----------------------------------------------------------------------
      IMessageMonitorManagerFactory &IMessageMonitorManagerFactory::singleton()
      {
        return *(Factory::singleton().get());
      }

      //-----------------------------------------------------------------------
      MessageMonitorManagerPtr IMessageMonitorManagerFactory::createMessageMonitorManager()
      {
        return MessageMonitorManager::create();
      }

      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      #pragma mark
      #pragma mark ILocationFactory
      #pragma mark

      //-----------------------------------------------------------------------
      ILocationFactory &ILocationFactory::singleton()
      {
        return *(Factory::singleton().get());
      }

      //-----------------------------------------------------------------------
      LocationPtr ILocationFactory::getForLocal(IAccountPtr account)
      {
        return Location::getForLocal(account);
      }

      //-----------------------------------------------------------------------
      LocationPtr ILocationFactory::getForFinder(IAccountPtr account)
      {
        return Location::getForFinder(account);
      }

      //-----------------------------------------------------------------------
      LocationPtr ILocationFactory::getForPeer(
                                               IPeerPtr peer,
                                               const char *locationID
                                               )
      {
        return Location::getForPeer(peer, locationID);
      }

      //-----------------------------------------------------------------------
      LocationPtr ILocationFactory::create(
                                           IMessageSourcePtr messageSource,
                                           const char *peerURI,
                                           const char *locationID
                                           )
      {
        return Location::create(messageSource, peerURI, locationID);
      }

      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      #pragma mark
      #pragma mark IPeerFactory
      #pragma mark

      //-----------------------------------------------------------------------
      IPeerFactory &IPeerFactory::singleton()
      {
        return *(Factory::singleton().get());
      }

      //-----------------------------------------------------------------------
      PeerPtr IPeerFactory::create(
                                   IAccountPtr account,
                                   IPeerFilePublicPtr peerFilePublic
                                   )
      {
        return Peer::create(account, peerFilePublic);
      }

      //-----------------------------------------------------------------------
      PeerPtr IPeerFactory::getFromSignature(
                                             IAccountPtr account,
                                             ElementPtr signedElement
                                             )
      {
        return Peer::getFromSignature(account, signedElement);
      }

      //-----------------------------------------------------------------------
      PeerPtr IPeerFactory::create(
                                   AccountPtr account,
                                   const char *peerURI
                                   )
      {
        return Peer::create(account, peerURI);
      }

      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      #pragma mark
      #pragma mark IPeerFilesFactory
      #pragma mark

      //-----------------------------------------------------------------------
      IPeerFilesFactory &IPeerFilesFactory::singleton()
      {
        return *(Factory::singleton().get());
      }

      //-----------------------------------------------------------------------
      PeerFilesPtr IPeerFilesFactory::generate(
                                               const char *password,
                                               ElementPtr signedSaltBundleEl
                                               )
      {
        return PeerFiles::generate(password, signedSaltBundleEl);
      }

      //-----------------------------------------------------------------------
      PeerFilesPtr IPeerFilesFactory::loadFromElement(
                                                      const char *password,
                                                      ElementPtr privatePeerRootElement
                                                      )
      {
        return PeerFiles::loadFromElement(password, privatePeerRootElement);
      }

      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      #pragma mark
      #pragma mark IPeerFilePrivateFactory
      #pragma mark

      //-----------------------------------------------------------------------
      IPeerFilePrivateFactory &IPeerFilePrivateFactory::singleton()
      {
        return *(Factory::singleton().get());
      }

      //-----------------------------------------------------------------------
      bool IPeerFilePrivateFactory::generate(
                                                  PeerFilesPtr peerFiles,
                                                  PeerFilePrivatePtr &outPeerFilePrivate,
                                                  PeerFilePublicPtr &outPeerFilePublic,
                                                  const char *password,
                                                  ElementPtr signedSalt
                                                  )
      {
        return PeerFilePrivate::generate(peerFiles, outPeerFilePrivate, outPeerFilePublic, password, signedSalt);
      }

      //-----------------------------------------------------------------------
      bool IPeerFilePrivateFactory::loadFromElement(
                                                         PeerFilesPtr peerFiles,
                                                         PeerFilePrivatePtr &outPeerFilePrivate,
                                                         PeerFilePublicPtr &outPeerFilePublic,
                                                         const char *password,
                                                         ElementPtr peerFileRootElement
                                                         )
      {
        return PeerFilePrivate::loadFromElement(peerFiles, outPeerFilePrivate, outPeerFilePublic, password, peerFileRootElement);
      }

      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      #pragma mark
      #pragma mark IPeerFilePublicFactory
      #pragma mark

      //-----------------------------------------------------------------------
      IPeerFilePublicFactory &IPeerFilePublicFactory::singleton()
      {
        return *(Factory::singleton().get());
      }

      //-----------------------------------------------------------------------
      PeerFilePublicPtr IPeerFilePublicFactory::loadFromElement(ElementPtr publicPeerRootElement)
      {
        return PeerFilePublic::loadFromElement(publicPeerRootElement);
      }

      //-----------------------------------------------------------------------
      PeerFilePublicPtr IPeerFilePublicFactory::createFromPublicKey(
                                                                    PeerFilesPtr peerFiles,
                                                                    DocumentPtr publicDoc,
                                                                    IRSAPublicKeyPtr publicKey,
                                                                    const String &peerURI
                                                                    )
      {
        return PeerFilePublic::createFromPublicKey(peerFiles, publicDoc, publicKey, peerURI);
      }

      //-----------------------------------------------------------------------
      PeerFilePublicPtr IPeerFilePublicFactory::loadFromElement(
                                                                PeerFilesPtr peerFiles,
                                                                DocumentPtr publicDoc
                                                                )
      {
        return PeerFilePublic::loadFromElement(peerFiles, publicDoc);
      }

      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      #pragma mark
      #pragma mark IPeerSubscriptionFactory
      #pragma mark

      //-----------------------------------------------------------------------
      IPeerSubscriptionFactory &IPeerSubscriptionFactory::singleton()
      {
        return *(Factory::singleton().get());
      }

      //-----------------------------------------------------------------------
      PeerSubscriptionPtr IPeerSubscriptionFactory::subscribeAll(
                                                                 IAccountPtr account,
                                                                 IPeerSubscriptionDelegatePtr delegate
                                                                 )
      {
        return PeerSubscription::subscribeAll(account, delegate);
      }

      //-----------------------------------------------------------------------
      PeerSubscriptionPtr IPeerSubscriptionFactory::subscribe(
                                                              IPeerPtr peer,
                                                              IPeerSubscriptionDelegatePtr delegate
                                                              )
      {
        return PeerSubscription::subscribe(peer, delegate);
      }

      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      #pragma mark
      #pragma mark IPublicationFactory
      #pragma mark

      //-----------------------------------------------------------------------
      IPublicationFactory &IPublicationFactory::singleton()
      {
        return *(Factory::singleton().get());
      }

      //-----------------------------------------------------------------------
      PublicationPtr IPublicationFactory::create(
                                                 LocationPtr creatorLocation,
                                                 const char *name,
                                                 const char *mimeType,
                                                 const SecureByteBlock &data,
                                                 const PublishToRelationshipsMap &publishToRelationships,
                                                 LocationPtr publishedLocation,
                                                 Time expires
                                                 )
      {
        return Publication::create(creatorLocation, name, mimeType, data, publishToRelationships, publishedLocation, expires);
      }

      //-----------------------------------------------------------------------
      PublicationPtr IPublicationFactory::create(
                                                 LocationPtr creatorLocation,
                                                 const char *name,
                                                 const char *mimeType,
                                                 DocumentPtr documentToBeAdopted,
                                                 const PublishToRelationshipsMap &publishToRelationships,
                                                 LocationPtr publishedLocation,
                                                 Time expires
                                                 )
      {
        return Publication::create(creatorLocation, name, mimeType, documentToBeAdopted, publishToRelationships, publishedLocation, expires);
      }

      //-----------------------------------------------------------------------
      PublicationPtr IPublicationFactory::create(
                                                 ULONG version,
                                                 ULONG baseVersion,
                                                 ULONG lineage,
                                                 LocationPtr creatorLocation,
                                                 const char *name,
                                                 const char *mimeType,
                                                 ElementPtr dataEl,
                                                 Encodings encoding,
                                                 const PublishToRelationshipsMap &publishToRelationships,
                                                 LocationPtr publishedLocation,
                                                 Time expires
                                                 )
      {
        return Publication::create(version, baseVersion, lineage, creatorLocation, name, mimeType, dataEl, encoding, publishToRelationships, publishedLocation, expires);
      }
      
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      //-----------------------------------------------------------------------
      #pragma mark
      #pragma mark IPublicationMetaDataFactory
      #pragma mark

      //-----------------------------------------------------------------------
      IPublicationMetaDataFactory &IPublicationMetaDataFactory::singleton()
      {
        return *(Factory::singleton().get());
      }

      //-----------------------------------------------------------------------
      PublicationMetaDataPtr IPublicationMetaDataFactory::creatPublicationMetaData(
                                                                                   ULONG version,
                                                                                   ULONG baseVersion,
                                                                                   ULONG lineage,
                                                                                   LocationPtr creatorLocation,
                                                                                   const char *name,
                                                                                   const char *mimeType,
                                                                                   Encodings encoding,
                                                                                   const PublishToRelationshipsMap &relationships,
                                                                                   LocationPtr publishedLocation,
                                                                                   Time expires
                                                                                   )
      {
        return PublicationMetaData::create(version, baseVersion, lineage, creatorLocation, name, mimeType, encoding, relationships, publishedLocation, expires);
      }
    }
  }
}