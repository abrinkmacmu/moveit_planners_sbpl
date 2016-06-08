////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2015, Andrew Dornbush
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
////////////////////////////////////////////////////////////////////////////////

/// \author Andrew Dornbush

#ifndef sbpl_interface_moveit_collision_checker_h
#define sbpl_interface_moveit_collision_checker_h

#include <moveit/planning_scene/planning_scene.h>
#include <moveit/robot_model/robot_model.h>
#include <moveit/robot_state/robot_state.h>
#include <ros/ros.h>
#include <sbpl_arm_planner/collision_checker.h>

namespace sbpl_interface {

class MoveItRobotModel;

class MoveItCollisionChecker : public sbpl::manip::CollisionChecker
{
public:

    typedef sbpl::manip::CollisionChecker Base;

    MoveItCollisionChecker();
    ~MoveItCollisionChecker();

    bool init(
        const MoveItRobotModel* robot_model,
        const moveit::core::RobotState& ref_state,
        const planning_scene::PlanningSceneConstPtr& scene);

    bool initialized() const;

    bool isStateValid(
        const std::vector<double>& angles,
        bool verbose,
        bool visualize,
        double& dist);

    bool isStateToStateValid(
        const std::vector<double>& angles0,
        const std::vector<double>& angles1,
        int& path_length,
        int& num_checks,
        double& dist);

    bool interpolatePath(
        const std::vector<double>& start,
        const std::vector<double>& end,
        std::vector<std::vector<double>>& path);

    visualization_msgs::MarkerArray getCollisionModelVisualization(
        const std::vector<double>& angles);

    visualization_msgs::MarkerArray getVisualization(const std::string& type);

private:

    const MoveItRobotModel* m_robot_model;

    planning_scene::PlanningSceneConstPtr m_scene;

    moveit::core::RobotStatePtr m_ref_state;

    ros::Publisher m_vpub;
};

} // namespace sbpl_interface

#endif
