#ifndef DETOURCROWDAGENT_H
#define DETOURCROWDAGENT_H

#include <Godot.hpp>
#include <vector>

class dtCrowdAgent;

namespace godot
{
    /**
     * @brief Parameters to initialize a DetourCrowdAgent.
     */
    struct DetourCrowdAgentParameters : public Reference
    {
        GODOT_CLASS(DetourCrowdAgentParameters, Reference)

    public:
        /**
         * @brief Called when .new() is called in gdscript
         */
        void _init() {}

        static void _register_methods();

        Vector3 position;

        // These two parameters will determine into which navigation mesh & crowd this agent will be put.
        // Make sure your DetourNavigationMesh supports the radius & height.
        float   radius;
        float   height;

        float   maxAcceleration;
        float   maxSpeed;

        // Check more in-depth descriptions of the optimizations here:
        // http://digestingduck.blogspot.com/2010/11/path-corridor-optimizations.html
        bool    anticipateTurns;    // If this agent should anticipate turns and move accordingly.
        bool    optimizeVisibility; // Optimize walked path based on visibility. Strongly recommended.
        bool    optimizeTopology;   // If shorter paths should be attempted under certain circumstances. Also recommended.

        bool    avoidObstacles;     // If this agent should try to avoid obstacles (other agents or dynamic obstacles).
        int     obstacleAvoidance;  // How much this agent should avoid obstacles. 0 - 3, with 0 being low and 3 high avoidance.
        float   separationWeight;   // How strongly the other agents should try to avoid this agent.
    };

    /**
     * @brief A single agent in a crowd.
     */
    class DetourCrowdAgent : public Reference
    {
        GODOT_CLASS(DetourCrowdAgent, Reference)

    public:
        static void _register_methods();

        /**
         * @brief Constructor.
         */
        DetourCrowdAgent();

        /**
         * @brief Destructor.
         */
        ~DetourCrowdAgent();

        /**
         * @brief Called when .new() is called in gdscript
         */
        void _init() {}

        /**
         * @brief Create a debug representation of this obstacle and attach it to the passed node.
         */
        void createDebugMesh(Node* node);

        /**
         * @brief The agent will start moving as close as possible towards the passed position.
         */
        void moveTowards(Vector3 position);

        /**
         * @brief Stops moving entirely.
         */
        void stop();

        /**
         * @brief Will update the shadows with the current values from the primary crowd.
         */
        void update();

    private:
        dtCrowdAgent*               _agent;
        std::vector<dtCrowdAgent*>  _shadows;
    };
}

#endif // DETOURCROWDAGENT_H