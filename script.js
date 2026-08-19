// --- UI NAVIGATION LOGIC ---
function showSection(sectionId) {
    document.querySelectorAll('.section').forEach(sec => sec.classList.remove('active'));
    document.getElementById(sectionId).classList.add('active');
}

// Fetch all data when the page first loads
document.addEventListener('DOMContentLoaded', () => {
    fetchEvents();
    fetchVenues();
    fetchVendors();
    fetchEquipment();
    fetchStaff();
});

// ==========================================
// 1. EVENTS API
// ==========================================
function fetchEvents() {
    fetch('/api/events').then(res => res.json()).then(data => {
        const tbody = document.getElementById('event-table-body');
        tbody.innerHTML = ''; 
        data.forEach(item => {
            tbody.innerHTML += `<tr><td>${item.id}</td><td><strong>${item.name}</strong></td><td>${item.date}</td></tr>`;
        });
    }).catch(err => console.log(err));
}

function createEvent() {
    const name = document.getElementById('eventName').value;
    const date = document.getElementById('eventDate').value;
    fetch('/api/events', {
        method: 'POST', headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ eventName: name, eventDate: date })
    }).then(() => { fetchEvents(); });
}

// ==========================================
// 2. VENUES API
// ==========================================
function fetchVenues() {
    fetch('/api/venues').then(res => res.json()).then(data => {
        const tbody = document.getElementById('venue-table-body');
        tbody.innerHTML = ''; 
        data.forEach(item => {
            tbody.innerHTML += `<tr><td>${item.id}</td><td><strong>${item.name}</strong></td><td>${item.capacity}</td></tr>`;
        });
    }).catch(err => console.log(err));
}

function createVenue() {
    const name = document.getElementById('venueName').value;
    const cap = document.getElementById('venueCapacity').value;
    fetch('/api/venues', {
        method: 'POST', headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ venueName: name, venueCapacity: cap })
    }).then(() => { fetchVenues(); });
}

// ==========================================
// 3. VENDORS API
// ==========================================
function fetchVendors() {
    fetch('/api/vendors').then(res => res.json()).then(data => {
        const tbody = document.getElementById('vendor-table-body');
        tbody.innerHTML = ''; 
        data.forEach(item => {
            tbody.innerHTML += `<tr><td>${item.id}</td><td><strong>${item.name}</strong></td><td>${item.service}</td></tr>`;
        });
    }).catch(err => console.log(err));
}

function createVendor() {
    const name = document.getElementById('vendorName').value;
    const srv = document.getElementById('vendorService').value;
    fetch('/api/vendors', {
        method: 'POST', headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ vendorName: name, vendorService: srv })
    }).then(() => { fetchVendors(); });
}

// ==========================================
// 4. EQUIPMENT API
// ==========================================
function fetchEquipment() {
    fetch('/api/equipment').then(res => res.json()).then(data => {
        const tbody = document.getElementById('equipment-table-body');
        tbody.innerHTML = ''; 
        data.forEach(item => {
            tbody.innerHTML += `<tr><td>${item.id}</td><td><strong>${item.name}</strong></td><td>${item.quantity}</td></tr>`;
        });
    }).catch(err => console.log(err));
}

function createEquipment() {
    const name = document.getElementById('equipName').value;
    const qty = document.getElementById('equipQuantity').value;
    fetch('/api/equipment', {
        method: 'POST', headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ equipName: name, equipQuantity: qty })
    }).then(() => { fetchEquipment(); });
}

// ==========================================
// 5. STAFF API
// ==========================================
function fetchStaff() {
    fetch('/api/staff').then(res => res.json()).then(data => {
        const tbody = document.getElementById('staff-table-body');
        tbody.innerHTML = ''; 
        data.forEach(item => {
            tbody.innerHTML += `<tr><td>${item.id}</td><td><strong>${item.name}</strong></td><td>${item.role}</td></tr>`;
        });
    }).catch(err => console.log(err));
}

function createStaff() {
    const name = document.getElementById('staffName').value;
    const role = document.getElementById('staffRole').value;
    fetch('/api/staff', {
        method: 'POST', headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ staffName: name, staffRole: role })
    }).then(() => { fetchStaff(); });
}

// ==========================================
// 6. BUDGET API (Placeholder)
// ==========================================
function calculateBudget() {
    document.getElementById('budget-output').innerText = "Calculating budget in C++...";
    // Future: fetch('/api/budget')...
}