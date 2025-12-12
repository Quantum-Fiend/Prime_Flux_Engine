import { useState, useEffect } from 'react'
import './App.css'

interface EngineMetrics {
    fps: number
    entityCount: number
    memoryUsage: number
    drawCalls: number
    aiTickRate: number
}

function App() {
    const [connected, setConnected] = useState(false)
    const [metrics, setMetrics] = useState<EngineMetrics>({
        fps: 0,
        entityCount: 0,
        memoryUsage: 0,
        drawCalls: 0,
        aiTickRate: 0
    })
    const [logs, setLogs] = useState<string[]>([
        '[Dashboard] Initializing...',
        '[Dashboard] Waiting for engine connection on ws://localhost:8080'
    ])

    useEffect(() => {
        // Simulate WebSocket connection (placeholder)
        const interval = setInterval(() => {
            if (connected) {
                // Simulate receiving metrics
                setMetrics({
                    fps: Math.floor(55 + Math.random() * 10),
                    entityCount: Math.floor(100 + Math.random() * 50),
                    memoryUsage: Math.floor(150 + Math.random() * 50),
                    drawCalls: Math.floor(500 + Math.random() * 200),
                    aiTickRate: Math.floor(25 + Math.random() * 10)
                })
            }
        }, 1000)

        return () => clearInterval(interval)
    }, [connected])

    const connectToEngine = () => {
        setConnected(true)
        addLog('[WebSocket] Connected to engine')
        addLog('[Engine] Receiving telemetry data...')
    }

    const disconnectFromEngine = () => {
        setConnected(false)
        addLog('[WebSocket] Disconnected from engine')
    }

    const addLog = (message: string) => {
        setLogs(prev => [...prev, `[${new Date().toLocaleTimeString()}] ${message}`].slice(-20))
    }

    return (
        <div className="container">
            <header style={{ marginBottom: '30px' }}>
                <h1 style={{ fontSize: '2.5rem', fontWeight: '700', marginBottom: '10px' }}>
                    ⚡ PrimeFlux Engine Dashboard
                </h1>
                <div style={{ display: 'flex', gap: '15px', alignItems: 'center' }}>
                    <span className={connected ? 'status-badge status-connected' : 'status-badge status-disconnected'}>
                        {connected ? '● Connected' : '○ Disconnected'}
                    </span>
                    {!connected ? (
                        <button className="btn" onClick={connectToEngine}>
                            Connect to Engine
                        </button>
                    ) : (
                        <button className="btn" onClick={disconnectFromEngine}>
                            Disconnect
                        </button>
                    )}
                </div>
            </header>

            <div className="grid grid-3" style={{ marginBottom: '30px' }}>
                <div className="card">
                    <div className="metric">
                        <span className="metric-label">FPS</span>
                        <span className="metric-value" style={{ color: metrics.fps > 55 ? '#10b981' : '#f59e0b' }}>
                            {metrics.fps}
                        </span>
                    </div>
                </div>

                <div className="card">
                    <div className="metric">
                        <span className="metric-label">Entity Count</span>
                        <span className="metric-value">{metrics.entityCount}</span>
                    </div>
                </div>

                <div className="card">
                    <div className="metric">
                        <span className="metric-label">Memory (MB)</span>
                        <span className="metric-value">{metrics.memoryUsage}</span>
                    </div>
                </div>

                <div className="card">
                    <div className="metric">
                        <span className="metric-label">Draw Calls</span>
                        <span className="metric-value">{metrics.drawCalls}</span>
                    </div>
                </div>

                <div className="card">
                    <div className="metric">
                        <span className="metric-label">AI Tick Rate</span>
                        <span className="metric-value">{metrics.aiTickRate} Hz</span>
                    </div>
                </div>
            </div>

            <div className="card">
                <h2 className="card-title">Engine Logs</h2>
                <div className="log-console">
                    {logs.map((log, index) => (
                        <div key={index} className="log-entry">{log}</div>
                    ))}
                </div>
            </div>

            <div className="grid grid-2" style={{ marginTop: '30px' }}>
                <div className="card">
                    <h2 className="card-title">Subsystems</h2>
                    <div style={{ display: 'flex', flexDirection: 'column', gap: '10px' }}>
                        <SubsystemStatus name="Rendering" active={connected} />
                        <SubsystemStatus name="Physics" active={connected} />
                        <SubsystemStatus name="Lua Scripting" active={connected} />
                        <SubsystemStatus name="Python AI" active={connected} />
                        <SubsystemStatus name="Rust Serialization" active={connected} />
                    </div>
                </div>

                <div className="card">
                    <h2 className="card-title">Quick Actions</h2>
                    <div style={{ display: 'flex', flexDirection: 'column', gap: '10px' }}>
                        <button className="btn" disabled={!connected}>Hot-Reload Lua Scripts</button>
                        <button className="btn" disabled={!connected}>Save Scene Snapshot</button>
                        <button className="btn" disabled={!connected}>Trigger AI Replanning</button>
                    </div>
                </div>
            </div>
        </div>
    )
}

function SubsystemStatus({ name, active }: { name: string, active: boolean }) {
    return (
        <div style={{
            display: 'flex',
            justifyContent: 'space-between',
            padding: '10px',
            background: 'rgba(0,0,0,0.2)',
            borderRadius: '6px'
        }}>
            <span>{name}</span>
            <span style={{ color: active ? '#10b981' : '#64748b' }}>
                {active ? '✓ Running' : '○ Offline'}
            </span>
        </div>
    )
}

export default App
