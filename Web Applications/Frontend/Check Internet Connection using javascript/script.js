const title = document.querySelector('h1');
const list = document.querySelector('ul');
const reload = document.querySelector('button');


// Event listener to check if the user is online
reload.addEventListener('click', () => {
    location.reload();
});


// Function to check if the user is online
function online() {
    title.textContent = 'You are online!';
    title.style.color = 'green';
    list.classList.add('hide');
    reload.classList.add('hide');
}

// Function to check if the user is offline
function offline() {
    title.textContent = 'You are offline!';
    title.style.color = 'red';
    list.classList.remove('hide');
    reload.classList.remove('hide');
}

// Check if the user is online or offline
window.onload = () => {
    if (navigator.onLine) {
        online();
    } else {
        offline();
    }
}

// Event listener to check if the user is online
window.addEventListener('online', online);

// Event listener to check if the user is offline
window.addEventListener('offline', offline);