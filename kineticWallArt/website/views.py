from django.http import HttpResponseRedirect
from django.shortcuts import reverse, render
from django.views.decorators.csrf import csrf_exempt
from collections import defaultdict
import json

from .models import Pattern, Cross


def index(request):
    arraypattern = defaultdict(list)
    elements = {"elem1", "elem2", "elem3", "elem4", "elem5", "elem6", "elem7", "elem8", "elem9"}
    patterns = Pattern.objects.all()
    for p in patterns:
        cross = Cross.objects.filter(pattern=p)
        for c in cross:
            crossdict = {
                "name": c.name,
                "illumination": c.illumination,
                "ill_cross1": c.ill_cross1,
                "ill_cross2": c.ill_cross2,
                "ill_cross3": c.ill_cross3,
                "ill_cross4": c.ill_cross4,
                "color_cross1": c.color_cross1,
                "color_cross2": c.color_cross2,
                "color_cross3": c.color_cross3,
                "color_cross4": c.color_cross4,
                "rotation": c.rotation
            }
            arraypattern[p.pk].append(crossdict)
    arraydict = dict(arraypattern)
    # print(arraydict)
    return render(request, 'index.html', context={'elements': elements, 'patterns': patterns, 'array': arraydict, 'jsarray': json.dumps(arraydict), 'nbar': index})


def animator(request):
    return render(request, 'animator.html')

def clear(request):
    if request.method == 'POST':
        print("clear")
        # TODO MQTT
    return HttpResponseRedirect(reverse('index'))


def sync(request):
    if request.method == 'POST':
        print("sync")
        # TODO MQTT
    return HttpResponseRedirect(reverse('index'))

@csrf_exempt
def setpattern(request):
    if request.method == 'POST':
        setpatterninfo = request.body.decode('utf-8')
        setpattern = json.loads(setpatterninfo)
        print(setpattern)
        # TODO MQTT
    return HttpResponseRedirect(reverse('index'))


def previewpattern(request):
    if request.method == 'POST':
        print("previewpattern")
        # TODO
    return HttpResponseRedirect(reverse('index'))


def deletepattern(request, pattern_id):
    pattern = Pattern.objects.get(pk=pattern_id)
    cross = Cross.objects.filter(pattern=pattern).delete()
    pattern.delete()
    return HttpResponseRedirect(reverse('index'))


@csrf_exempt
def savepattern(request):
    if request.method == 'POST':
        getpatterninfo = request.body.decode('utf-8')
        patterninfo = json.loads(getpatterninfo)
        # print(patterninfo)
        patternname = patterninfo["name"]

        checkDB = patterninfo["checkDB"]

        if checkDB != "":
            if Pattern.objects.filter(pk=checkDB).exists():
                pattern = Pattern.objects.get(pk=checkDB)
                pattern.name = patternname
                pattern.save()
                print("EXISTS")
                Cross.objects.filter(pattern=pattern).delete()
        else:
            pattern = Pattern()
            pattern.name = patternname
            pattern.save()

        listitem = patterninfo["listarray"]
        for item in listitem:
            cross = Cross(name=item["name"], illumination=item["illumination"], ill_cross1=item["ill_cross1"],
                          ill_cross2=item["ill_cross2"], ill_cross3=item["ill_cross3"], ill_cross4=item["ill_cross4"],
                          color_cross1=item["color_cross1"], color_cross2=item["color_cross2"],
                          color_cross3=item["color_cross3"],
                          color_cross4=item["color_cross4"], rotation=item["rotation"])
            cross.pattern = pattern
            # print(item)
            cross.save()
    return HttpResponseRedirect(reverse('index'))
