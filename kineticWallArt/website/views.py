from django.http import HttpResponseRedirect
from django.shortcuts import reverse, render
from django.views.decorators.csrf import csrf_exempt
import json

from .models import Image, Cross


def index(request):
    elements = {"elem1", "elem2", "elem3", "elem4", "elem5", "elem6", "elem7", "elem8", "elem9"}
    images = Image.objects.all()
    return render(request, 'index.html', context={'elements': elements, 'images': images})


def clear(request):
    if request.method == 'POST':
        print("clear")
    return HttpResponseRedirect(reverse('index'))


def sync(request):
    if request.method == 'POST':
        print("sync")
    return HttpResponseRedirect(reverse('index'))


def setpattern(request):
    if request.method == 'POST':
        print("setpattern")
    return HttpResponseRedirect(reverse('index'))


def previewpattern(request):
    if request.method == 'POST':
        print("previewpattern")
    return HttpResponseRedirect(reverse('index'))


def deletepattern(request):
    if request.method == 'POST':
        print("deletepattern")
    return HttpResponseRedirect(reverse('index'))


@csrf_exempt
def savepattern(request):
    if request.method == 'POST':
        getimageinfo = request.body.decode('utf-8')
        imageinfo = json.loads(getimageinfo)
        print(imageinfo)
        imagename = imageinfo["name"]

        image = Image()
        image.name = imagename
        image.save()

        listitem = imageinfo["listarray"]
        for item in listitem:
            cross = Cross(name=item["name"], illumination=item["illumination"], ill_cross1=item["ill_cross1"],
                              ill_cross2=item["ill_cross2"], ill_cross3=item["ill_cross3"], ill_cross4=item["ill_cross4"],
                              color_cross1=item["color_cross1"], color_cross2=item["color_cross2"], color_cross3=item["color_cross3"],
                              color_cross4=item["color_cross4"], rotation=item["rotation"])
            cross.image = image
            # print(item)
            cross.save()
    return HttpResponseRedirect(reverse('index'))
