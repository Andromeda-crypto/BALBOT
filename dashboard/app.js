const state = {
  safety: "BALANCING",
  t: 0,
  data: [],
  events: []
};

const el = id => document.getElementById(id);

function logEvent(msg) {
  const time = new Date().toLocaleTimeString();
  state.events.unshift(`[${time}] ${msg}`);
  state.events = state.events.slice(0, 30);
  el("events").innerHTML = state.events.map(e => `<div class="event">${e}</div>`).join("");
}

const chartOptions = {
  responsive: true,
  maintainAspectRatio: false,
  animation: false,
  plugins: { legend: { labels: { color: "#7b8491" } } },
  scales: {
    x: { ticks: { color: "#7b8491" }, grid: { color: "#20252b" } },
    y: { ticks: { color: "#7b8491" }, grid: { color: "#20252b" } }
  }
};

const angleChart = new Chart(el("angleChart"), {
  type: "line",
  data: {
    labels: [],
    datasets: [
      { label: "Angle", data: [], borderColor: "#fbbf24", pointRadius: 0, tension: .25 },
      { label: "Target", data: [], borderColor: "#60a5fa", pointRadius: 0, borderDash: [5,5] }
    ]
  },
  options: chartOptions
});

const motorChart = new Chart(el("motorChart"), {
  type: "line",
  data: {
    labels: [],
    datasets: [
      { label: "PID", data: [], borderColor: "#c084fc", pointRadius: 0 },
      { label: "RPM L", data: [], borderColor: "#22c55e", pointRadius: 0 },
      { label: "RPM R", data: [], borderColor: "#86efac", pointRadius: 0 }
    ]
  },
  options: chartOptions
});

function mockTelemetry() {
  state.t += 0.05;

  const angle = Math.sin(state.t * 2.2) * 4.5 * Math.exp(-0.015 * state.t)
              + Math.sin(state.t * 6.7) * 0.35
              + (Math.random() - 0.5) * 0.25;

  const output = Math.max(-255, Math.min(255, -angle * 18 + (Math.random() - 0.5) * 8));

  return {
    angle,
    target: 0.0,
    output,
    rpm_l: Math.abs(output) * 1.4 + Math.random() * 4,
    rpm_r: Math.abs(output) * 1.35 + Math.random() * 4,
    pwm_l: output,
    pwm_r: output * 0.97,
    kp: Number(el("kp").value || 20),
    ki: Number(el("ki").value || 0),
    kd: Number(el("kd").value || 0.8),
    armed: state.safety !== "DISARMED" && state.safety !== "ESTOP",
    safety: state.safety,
    uptime: state.t,
    battery: 7.8 + Math.sin(state.t * 0.08) * 0.05,
    cpu: 32 + Math.round(Math.random() * 5),
    heap: 48 + Math.round(Math.random() * 3),
    temp: 42 + Math.round(Math.random() * 2),
    accel_x: angle / 90,
    accel_z: 0.98,
    gyro_y: output / 40
  };
}

function updateUI(d) {
  el("angle").textContent = d.angle.toFixed(2);
  el("target").textContent = d.target.toFixed(1);
  el("cpu").textContent = d.cpu;
  el("heap").textContent = d.heap;
  el("battery").textContent = d.battery.toFixed(2);
  el("footerBattery").textContent = d.battery.toFixed(2);
  el("temp").textContent = d.temp;
  el("accel_x").textContent = d.accel_x.toFixed(3);
  el("accel_z").textContent = d.accel_z.toFixed(3);
  el("gyro_y").textContent = d.gyro_y.toFixed(2);
  el("raw_angle").textContent = d.angle.toFixed(2);
  el("uptime").textContent = d.uptime.toFixed(1);

  el("m_angle").textContent = d.angle.toFixed(1) + "°";
  el("m_output").textContent = d.output.toFixed(0);
  el("m_rpm_l").textContent = d.rpm_l.toFixed(0);
  el("m_rpm_r").textContent = d.rpm_r.toFixed(0);

  el("horizonLine").style.transform = `rotate(${d.angle}deg)`;

  const pill = el("safetyPill");
  pill.textContent = d.safety;
  pill.className = "pill " + d.safety.toLowerCase();

  state.data.push(d);
  state.data = state.data.slice(-120);

  const labels = state.data.map(x => x.uptime.toFixed(1));

  angleChart.data.labels = labels;
  angleChart.data.datasets[0].data = state.data.map(x => x.angle);
  angleChart.data.datasets[1].data = state.data.map(x => x.target);
  angleChart.update();

  motorChart.data.labels = labels;
  motorChart.data.datasets[0].data = state.data.map(x => x.output);
  motorChart.data.datasets[1].data = state.data.map(x => x.rpm_l);
  motorChart.data.datasets[2].data = state.data.map(x => x.rpm_r);
  motorChart.update();
}

function renderNodes() {
  const nodes = ["/sensor", "/controller", "/motor_l", "/motor_r", "/dashboard"];
  el("nodes").innerHTML = nodes.map((n, i) => `
    <div class="node">
      <span><span class="node-dot"></span>${n}</span>
      <span>${i === 4 ? 20 : 100} Hz</span>
    </div>
  `).join("");
}

document.querySelectorAll(".tab").forEach(btn => {
  btn.addEventListener("click", () => {
    document.querySelectorAll(".tab").forEach(b => b.classList.remove("active"));
    document.querySelectorAll(".screen").forEach(s => s.classList.remove("active"));
    btn.classList.add("active");
    el(btn.dataset.tab).classList.add("active");
  });
});

el("arm").onclick = () => { state.safety = "ARMED"; logEvent("ARM command issued"); };
el("disarm").onclick = () => { state.safety = "DISARMED"; logEvent("DISARM command issued"); };
el("estop").onclick = () => { state.safety = "ESTOP"; logEvent("EMERGENCY STOP"); };
el("apply").onclick = () => logEvent(`Apply gains Kp=${el("kp").value} Ki=${el("ki").value} Kd=${el("kd").value}`);

el("kp").value = 20;
el("ki").value = 0;
el("kd").value = 0.8;

renderNodes();
logEvent("Dashboard booted in MOCK mode");

setInterval(() => {
  updateUI(mockTelemetry());
}, 50);