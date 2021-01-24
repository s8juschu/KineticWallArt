from django.http import HttpResponseRedirect
from django.shortcuts import reverse, render


def index(request):
    return render(request, 'index.html')


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


def savepattern(request):
    if request.method == 'POST':
        print("savepattern")
    return HttpResponseRedirect(reverse('index'))
