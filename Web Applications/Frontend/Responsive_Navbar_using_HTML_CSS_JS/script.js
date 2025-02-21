/*
    - when click to the hamburger icon, show/hide navbar also toggle between bars/x-mark icon.
*/

const navbar = document.querySelector('.navbar');
const bars = document.querySelector('.fa-bars');
const xmark = document.querySelector('.fa-xmark');
const hamburgerMenu = document.querySelector('.hamburger');

hamburgerMenu.addEventListener('click', () => {
    bars.classList.toggle('active');
    xmark.classList.toggle('active');
    navbar.classList.toggle('active');
});