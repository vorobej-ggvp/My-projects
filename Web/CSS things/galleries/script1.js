const slideGallery = document.querySelector(".slides");
const slides = slideGallery.querySelectorAll("div");
const scrollbarThumb = document.querySelector(".thumb");
const slidesCount = slides.length;
const slideHeight = 720;
const marginTop = 16;

const scrollThumb = () => {
    const index = Math.floor(slideGallery.scrollTop / slideHeight);
    scrollbarThumb.style.height = `${((index + 1) / slidesCount) * slideHeight}px`;
}

const scrollToElement = (el) => {
    const index = parseInt(el.dataset.id, 10);
    slideGallery.scrollTo(0, index * slideHeight + marginTop);
}

const thumbnailsContainer = document.querySelector(".thumbnails");
if (thumbnailsContainer) {
    thumbnailsContainer.innerHTML += [...slides]
        .map(
            (slide, i) => `<img src="${slide.querySelector("img").src}" data-id="${i}">`
        )
        .join("");

    document.querySelectorAll(".thumbnails img").forEach((el) => {
        el.addEventListener("click", () => scrollToElement(el));
    });
}

slideGallery.addEventListener("scroll", (e) => scrollThumb());

scrollThumb();