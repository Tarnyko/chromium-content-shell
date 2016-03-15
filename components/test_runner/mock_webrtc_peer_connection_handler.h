// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_TEST_RUNNER_MOCK_WEBRTC_PEER_CONNECTION_HANDLER_H_
#define COMPONENTS_TEST_RUNNER_MOCK_WEBRTC_PEER_CONNECTION_HANDLER_H_

#include <map>

#include "base/basictypes.h"
#include "components/test_runner/web_task.h"
#include "third_party/WebKit/public/platform/WebRTCPeerConnectionHandler.h"
#include "third_party/WebKit/public/platform/WebRTCSessionDescription.h"
#include "third_party/WebKit/public/platform/WebRTCSessionDescriptionRequest.h"
#include "third_party/WebKit/public/platform/WebRTCStatsRequest.h"

namespace blink {
class WebRTCPeerConnectionHandlerClient;
};

namespace test_runner {

class TestInterfaces;

class MockWebRTCPeerConnectionHandler
    : public blink::WebRTCPeerConnectionHandler {
 public:
  MockWebRTCPeerConnectionHandler(
      blink::WebRTCPeerConnectionHandlerClient* client,
      TestInterfaces* interfaces);
  ~MockWebRTCPeerConnectionHandler() override;

  // WebRTCPeerConnectionHandler related methods
  bool initialize(const blink::WebRTCConfiguration& configuration,
                  const blink::WebMediaConstraints& constraints) override;

  void createOffer(const blink::WebRTCSessionDescriptionRequest& request,
                   const blink::WebMediaConstraints& constraints) override;
  void createOffer(const blink::WebRTCSessionDescriptionRequest& request,
                   const blink::WebRTCOfferOptions& options) override;
  void createAnswer(const blink::WebRTCSessionDescriptionRequest& request,
                    const blink::WebMediaConstraints& constraints) override;
  void setLocalDescription(
      const blink::WebRTCVoidRequest& request,
      const blink::WebRTCSessionDescription& local_description) override;
  void setRemoteDescription(
      const blink::WebRTCVoidRequest& request,
      const blink::WebRTCSessionDescription& remote_description) override;
  blink::WebRTCSessionDescription localDescription() override;
  blink::WebRTCSessionDescription remoteDescription() override;
  bool updateICE(const blink::WebRTCConfiguration& configuration,
                 const blink::WebMediaConstraints& constraints) override;
  bool addICECandidate(const blink::WebRTCICECandidate& ice_candidate) override;
  bool addICECandidate(const blink::WebRTCVoidRequest& request,
                       const blink::WebRTCICECandidate& ice_candidate) override;
  bool addStream(const blink::WebMediaStream& stream,
                 const blink::WebMediaConstraints& constraints) override;
  void removeStream(const blink::WebMediaStream& stream) override;
  void getStats(const blink::WebRTCStatsRequest& request) override;
  blink::WebRTCDataChannelHandler* createDataChannel(
      const blink::WebString& label,
      const blink::WebRTCDataChannelInit& init) override;
  blink::WebRTCDTMFSenderHandler* createDTMFSender(
      const blink::WebMediaStreamTrack& track) override;
  void stop() override;

  // WebTask related methods
  WebTaskList* mutable_task_list() { return &task_list_; }

 private:
  MockWebRTCPeerConnectionHandler();

  // UpdateRemoteStreams uses the collection of |local_streams_| to create
  // remote MediaStreams with the same number of tracks and notifies |client_|
  // about added and removed streams. It's triggered when setRemoteDescription
  // is called.
  void UpdateRemoteStreams();

  blink::WebRTCPeerConnectionHandlerClient* client_;
  bool stopped_;
  WebTaskList task_list_;
  blink::WebRTCSessionDescription local_description_;
  blink::WebRTCSessionDescription remote_description_;
  int stream_count_;
  TestInterfaces* interfaces_;
  typedef std::map<std::string, blink::WebMediaStream> StreamMap;
  StreamMap local_streams_;
  StreamMap remote_streams_;

  DISALLOW_COPY_AND_ASSIGN(MockWebRTCPeerConnectionHandler);
};

}  // namespace test_runner

#endif  // COMPONENTS_TEST_RUNNER_MOCK_WEBRTC_PEER_CONNECTION_HANDLER_H_
