const onPageLoad = () => {
    const field = document.getElementsByClassName('field')[0];
    const follower = document.querySelector('.point');
    
    const placeField = () => {
        if(field) {
            field.style.transform = `translate(${window.innerWidth * 0.5}px)`;
            console.log(1);
        }
        else {
            console.log(0);
        }
    }
    placeField();

    document.addEventListener('mousemove', (event) => {
        follower.style.left = `${event.clientX}px`;
        follower.style.top = `${event.clientY}px`;
    })

}

window.addEventListener('DOMContentLoaded', onPageLoad);

//mousemove
//mouseEnter
//mouseLeave
// .field {position: relative;}