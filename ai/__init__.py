"""
PrimeFlux AI Subsystem
Entry point for Python AI module
"""

from behavior_tree import init_ai_for_entity, tick_ai, cleanup_ai_for_entity

__all__ = [
    'init_ai_for_entity',
    'tick_ai',
    'cleanup_ai_for_entity'
]

print("[Python AI] PrimeFlux AI subsystem loaded")
