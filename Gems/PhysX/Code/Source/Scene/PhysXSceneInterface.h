/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates, or
* a third party where indicated.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
#pragma once

#include <AzCore/Interface/Interface.h>
#include <AzFramework/Physics/PhysicsScene.h>
#include <AzFramework/Physics/Common/PhysicsEvents.h>

namespace AzPhysics
{
    struct SimulatedBody;
}

namespace PhysX
{
    class PhysXSystem;

    class PhysXSceneInterface
        : public AZ::Interface<AzPhysics::SceneInterface>::Registrar
    {
    public:
        explicit PhysXSceneInterface(PhysXSystem* physxSystem);

        // AzPhysics::SceneInterface ...
        AzPhysics::SceneHandle GetSceneHandle(const AZStd::string& sceneName) override;
        void StartSimulation(AzPhysics::SceneHandle sceneHandle, float deltatime) override;
        void FinishSimulation(AzPhysics::SceneHandle sceneHandle) override;
        void SetEnabled(AzPhysics::SceneHandle sceneHandle, bool enable) override;
        bool IsEnabled(AzPhysics::SceneHandle sceneHandle) const override;
        AzPhysics::SimulatedBodyHandle AddSimulatedBody(AzPhysics::SceneHandle sceneHandle, const AzPhysics::SimulatedBodyConfiguration* simulatedBodyConfig) override;
        AzPhysics::SimulatedBodyHandleList AddSimulatedBodies(AzPhysics::SceneHandle sceneHandle, const AzPhysics::SimulatedBodyConfigurationList& simulatedBodyConfigs) override;
        AzPhysics::SimulatedBody* GetSimulatedBodyFromHandle(AzPhysics::SceneHandle sceneHandle, AzPhysics::SimulatedBodyHandle bodyHandle) override;
        AzPhysics::SimulatedBodyList GetSimulatedBodiesFromHandle(AzPhysics::SceneHandle sceneHandle, const AzPhysics::SimulatedBodyHandleList& bodyHandles) override;
        void RemoveSimulatedBody(AzPhysics::SceneHandle sceneHandle, AzPhysics::SimulatedBodyHandle bodyHandle) override;
        void RemoveSimulatedBodies(AzPhysics::SceneHandle sceneHandle, const AzPhysics::SimulatedBodyHandleList& bodyHandles) override;
        void EnableSimulationOfBody(AzPhysics::SceneHandle sceneHandle, AzPhysics::SimulatedBodyHandle bodyHandle) override;
        void DisableSimulationOfBody(AzPhysics::SceneHandle sceneHandle, AzPhysics::SimulatedBodyHandle bodyHandle) override;
        AzPhysics::SceneQueryHits QueryScene(AzPhysics::SceneHandle sceneHandle, const AzPhysics::SceneQueryRequest* request) override;
        AzPhysics::SceneQueryHitsList QuerySceneBatch(AzPhysics::SceneHandle sceneHandle, const AzPhysics::SceneQueryRequests& requests) override;
        [[nodiscard]] bool QuerySceneAsync(AzPhysics::SceneHandle sceneHandle, AzPhysics::SceneQuery::AsyncRequestId requestId,
            const AzPhysics::SceneQueryRequest* request, AzPhysics::SceneQuery::AsyncCallback callback) override;
        [[nodiscard]] bool QuerySceneAsyncBatch(AzPhysics::SceneHandle sceneHandle, AzPhysics::SceneQuery::AsyncRequestId requestId,
            const AzPhysics::SceneQueryRequests& requests, AzPhysics::SceneQuery::AsyncBatchCallback callback) override;
        void SuppressCollisionEvents(AzPhysics::SceneHandle sceneHandle,
            const AzPhysics::SimulatedBodyHandle& bodyHandleA,
            const AzPhysics::SimulatedBodyHandle& bodyHandleB) override;
        void UnsuppressCollisionEvents(AzPhysics::SceneHandle sceneHandle,
            const AzPhysics::SimulatedBodyHandle& bodyHandleA,
            const AzPhysics::SimulatedBodyHandle& bodyHandleB) override;
        void SetGravity(AzPhysics::SceneHandle sceneHandle, const AZ::Vector3& gravity) override;
        AZ::Vector3 GetGravity(AzPhysics::SceneHandle sceneHandle) const override;
        void RegisterSceneConfigurationChangedEventHandler(AzPhysics::SceneHandle sceneHandle, AzPhysics::SceneEvents::OnSceneConfigurationChanged::Handler& handler) override;
        void RegisterSimulationBodyAddedHandler(AzPhysics::SceneHandle sceneHandle, AzPhysics::SceneEvents::OnSimulationBodyAdded::Handler& handler) override;
        void RegisterSimulationBodyRemovedHandler(AzPhysics::SceneHandle sceneHandle, AzPhysics::SceneEvents::OnSimulationBodyRemoved::Handler& handler) override;
        void RegisterSimulationBodySimulationEnabledHandler(AzPhysics::SceneHandle sceneHandle, AzPhysics::SceneEvents::OnSimulationBodySimulationEnabled::Handler& handler) override;
        void RegisterSimulationBodySimulationDisabledHandler(AzPhysics::SceneHandle sceneHandle, AzPhysics::SceneEvents::OnSimulationBodySimulationDisabled::Handler& handler) override;
        void RegisterSceneSimulationStartHandler(AzPhysics::SceneHandle sceneHandle, AzPhysics::SceneEvents::OnSceneSimulationStartHandler& handler) override;
        void RegisterSceneSimulationFinishHandler(AzPhysics::SceneHandle sceneHandle, AzPhysics::SceneEvents::OnSceneSimulationFinishHandler& handler) override;
        void RegisterSceneActiveSimulatedBodiesHandler(AzPhysics::SceneHandle sceneHandle, AzPhysics::SceneEvents::OnSceneActiveSimulatedBodiesEvent::Handler& handler) override;
        void RegisterSceneCollisionEventHandler(AzPhysics::SceneHandle sceneHandle, AzPhysics::SceneEvents::OnSceneCollisionsEvent::Handler& handler) override;
        void RegisterSceneTriggersEventHandler(AzPhysics::SceneHandle sceneHandle, AzPhysics::SceneEvents::OnSceneTriggersEvent::Handler& handler) override;
        void RegisterSceneGravityChangedEvent(AzPhysics::SceneHandle sceneHandle, AzPhysics::SceneEvents::OnSceneGravityChangedEvent::Handler& handler) override;
    private:
        PhysXSystem* m_physxSystem = nullptr;
    };
}