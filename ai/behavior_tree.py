"""
PrimeFlux AI Subsystem - Behavior Tree Implementation
Provides AI decision-making capabilities for NPCs
"""

from enum import Enum
from typing import Callable, List, Optional, Any
from dataclasses import dataclass


class NodeStatus(Enum):
    """Status returned by behavior tree nodes"""
    SUCCESS = 1
    FAILURE = 2
    RUNNING = 3


@dataclass
class AIContext:
    """Context data passed to behavior tree nodes"""
    entity_id: int
    delta_time: float
    blackboard: dict  # Shared data storage


class BehaviorNode:
    """Base class for all behavior tree nodes"""
    
    def __init__(self, name: str = "Node"):
        self.name = name
    
    def tick(self, context: AIContext) -> NodeStatus:
        """Execute this node's logic"""
        raise NotImplementedError("Subclasses must implement tick()")


class ActionNode(BehaviorNode):
    """Leaf node that performs an action"""
    
    def __init__(self, name: str, action: Callable[[AIContext], NodeStatus]):
        super().__init__(name)
        self.action = action
    
    def tick(self, context: AIContext) -> NodeStatus:
        return self.action(context)


class ConditionNode(BehaviorNode):
    """Leaf node that checks a condition"""
    
    def __init__(self, name: str, condition: Callable[[AIContext], bool]):
        super().__init__(name)
        self.condition = condition
    
    def tick(self, context: AIContext) -> NodeStatus:
        return NodeStatus.SUCCESS if self.condition(context) else NodeStatus.FAILURE


class SequenceNode(BehaviorNode):
    """Composite node that runs children in sequence until one fails"""
    
    def __init__(self, name: str = "Sequence"):
        super().__init__(name)
        self.children: List[BehaviorNode] = []
    
    def add_child(self, child: BehaviorNode):
        self.children.append(child)
        return self
    
    def tick(self, context: AIContext) -> NodeStatus:
        for child in self.children:
            status = child.tick(context)
            if status != NodeStatus.SUCCESS:
                return status
        return NodeStatus.SUCCESS


class SelectorNode(BehaviorNode):
    """Composite node that runs children until one succeeds"""
    
    def __init__(self, name: str = "Selector"):
        super().__init__(name)
        self.children: List[BehaviorNode] = []
    
    def add_child(self, child: BehaviorNode):
        self.children.append(child)
        return self
    
    def tick(self, context: AIContext) -> NodeStatus:
        for child in self.children:
            status = child.tick(context)
            if status != NodeStatus.FAILURE:
                return status
        return NodeStatus.FAILURE


class BehaviorTree:
    """Main behavior tree class"""
    
    def __init__(self, root: BehaviorNode):
        self.root = root
    
    def tick(self, entity_id: int, delta_time: float) -> NodeStatus:
        """Execute the behavior tree"""
        context = AIContext(
            entity_id=entity_id,
            delta_time=delta_time,
            blackboard={}
        )
        return self.root.tick(context)


# ============================================
# Example AI Behaviors
# ============================================

def create_patrol_behavior() -> BehaviorTree:
    """Create a simple patrol behavior tree"""
    
    def is_enemy_visible(ctx: AIContext) -> bool:
        # TODO: Query C++ engine for enemy visibility
        return ctx.blackboard.get("enemy_visible", False)
    
    def patrol_action(ctx: AIContext) -> NodeStatus:
        print(f"[AI] Entity {ctx.entity_id} is patrolling")
        return NodeStatus.SUCCESS
    
    def chase_action(ctx: AIContext) -> NodeStatus:
        print(f"[AI] Entity {ctx.entity_id} is chasing enemy")
        return NodeStatus.SUCCESS
    
    # Build behavior tree: If enemy visible, chase; otherwise patrol
    root = SelectorNode("Root")
    
    chase_sequence = SequenceNode("Chase")
    chase_sequence.add_child(ConditionNode("EnemyVisible", is_enemy_visible))
    chase_sequence.add_child(ActionNode("Chase", chase_action))
    
    root.add_child(chase_sequence)
    root.add_child(ActionNode("Patrol", patrol_action))
    
    return BehaviorTree(root)


# ============================================
# C++ Interop Functions (called via pybind11)
# ============================================

_behavior_trees = {}  # Store behavior trees by entity ID


def init_ai_for_entity(entity_id: int, behavior_type: str = "patrol"):
    """Initialize AI for an entity"""
    print(f"[Python AI] Initializing AI for entity {entity_id}")
    
    if behavior_type == "patrol":
        _behavior_trees[entity_id] = create_patrol_behavior()
    else:
        print(f"[Python AI] Unknown behavior type: {behavior_type}")


def tick_ai(entity_id: int, delta_time: float):
    """Tick AI for an entity (called from C++ update loop)"""
    if entity_id in _behavior_trees:
        tree = _behavior_trees[entity_id]
        status = tree.tick(entity_id, delta_time)
        # print(f"[Python AI] Entity {entity_id} AI tick: {status}")


def cleanup_ai_for_entity(entity_id: int):
    """Cleanup AI for an entity"""
    if entity_id in _behavior_trees:
        del _behavior_trees[entity_id]
        print(f"[Python AI] Cleaned up AI for entity {entity_id}")


if __name__ == "__main__":
    # Test the behavior tree
    print("Testing PrimeFlux AI Subsystem...")
    
    tree = create_patrol_behavior()
    status = tree.tick(entity_id=1, delta_time=0.016)
    print(f"Behavior tree result: {status}")
